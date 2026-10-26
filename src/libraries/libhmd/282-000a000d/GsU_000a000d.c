#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
	u_char  u0, v0;
	u_short clut;
	u_char  u1, v1;
	u_short tpage;
	u_char  u2, v2;
	u_short pad2;
	u_short n0, tvx0;
	u_short n1, tvx1;
	u_short n2, tvx2;
} HMD_P_GT3;

static void func_000004A0(u_long *scratch, GsADIV_GT3 *ifo, int level);

/*
 * Active Sub-divide Depth-Cued Gouraud Textured Triangle (GsU_000a000d)
 */
u_long *GsU_000a000d(GsARGUNIT *sp)
{
	GsARGUNIT_NORMAL	*ap = (GsARGUNIT_NORMAL *)sp;
	SVECTOR			*vp = ap->vertop;
	SVECTOR			*np = ap->nortop;
	GsADIV_GT3		*ifo;
	GsADIV_P_GT3		*p1;
	HMD_P_GT3		*tp;
	POLY_GT3		*si;
	u_long			*scratch = (u_long *)(ap + 1);
	int			i;
	int			num;

	num = *(ap->primp) >> 16;

	ap->primp++;
	tp = (HMD_P_GT3 *)(ap->primtop + (*(ap->primp) & 0x00ffffff));

	ifo = (GsADIV_GT3 *)scratch;
	scratch += sizeof(GsADIV_GT3) / 4;
	p1 = (GsADIV_P_GT3 *)scratch;

	ifo->limit = *(ap->primp) >> 24;
	ifo->hwd0 = HWD0 / 2;
	ifo->vwd0 = VWD0 / 2;
	ifo->adivz = GsADIVZ;
	ifo->adivw = GsADIVW;
	ifo->adivh = GsADIVH;
	ifo->pk = (u_long *)ap->out_packetp;
	ifo->org = (u_long *)ap->tagp->org;
	ifo->shift = ap->shift;

	setPolyGT3(&ifo->si);
	ifo->si.r0 = 0x80;
	ifo->si.g0 = 0x80;
	ifo->si.b0 = 0x80;
	gte_ldrgb((u_long *)&ifo->si.r0);

	si = (POLY_GT3 *)ifo->pk;

	for (i = 0; i < num; i++, tp++) {
		gte_ldv3(&vp[tp->tvx0], &vp[tp->tvx1], &vp[tp->tvx2]);
		gte_rtpt();

		*(u_long *)&si->u0 = *(u_long *)&tp->u0;
		*(u_long *)&si->u2 = *(u_long *)&tp->u2;

		gte_stflg(&ifo->flg);
		gte_nclip();
		gte_stopz(&ifo->otz);

		if (ifo->otz <= 0) {
			continue;
		}
		if (ifo->flg & 0x00040000) {
			continue;
		}

		gte_stsxy3_gt3((u_long *)si);
		gte_avsz3();
		gte_stotz(&ifo->otz);
		gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
		gte_ncdt();
		*(u_long *)&si->u1 = *(u_long *)&tp->u1;

		ifo->tag = (u_long *)(ifo->org + (ifo->otz >> ifo->shift));
		gte_strgb3(&si->r0, &si->r1, &si->r2);

		if (ifo->otz < ifo->adivz) {
			goto divide;
		}
		if (ifo->flg & 0x80000000) {
			goto divide;
		}

		*(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x09000000;
		*ifo->tag = (u_long)si & 0x00ffffff;

		si++;
		continue;

divide:
		*(SVECTOR *)&p1->vt[0] = vp[tp->tvx0];
		*(SVECTOR *)&p1->vt[1] = vp[tp->tvx1];
		*(SVECTOR *)&p1->vt[2] = vp[tp->tvx2];
		*(u_long *)&p1->vt[0].col.r = *(u_long *)&si->r0;
		*(u_long *)&p1->vt[1].col.r = *(u_long *)&si->r1;
		*(u_long *)&p1->vt[2].col.r = *(u_long *)&si->r2;
		*(u_short *)&p1->vt[0].tu = *(u_short *)&tp->u0;
		*(u_short *)&p1->vt[1].tu = *(u_short *)&tp->u1;
		*(u_short *)&p1->vt[2].tu = *(u_short *)&tp->u2;
		ifo->si.clut = tp->clut;
		ifo->si.tpage = tp->tpage;

		ifo->pk = (u_long *)si;

		func_000004A0(scratch, ifo, 0);

		si = (POLY_GT3 *)ifo->pk;
	}
	GsOUT_PACKET_P = (PACKET *)si;
	return(ap->primp+1);
}
