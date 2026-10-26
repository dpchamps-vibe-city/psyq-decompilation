#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <inline_c.h>
#include <gtemac.h>
#include <libgpu.h>
#include <libgs.h>
#include <asm.h>
#include <libhmd.h>

typedef struct {
	u_char	r0, g0, b0, code;
	u_short	n0, v0;
	u_short	v1, v2;
	u_short	v3, pad;
} HMD_P_F4;

static void func_00000488(u_long *, GsADIV_F4 *, int);

/*
 * Active Sub-divide Depth-Cued Flat Quadrangle (GsU_000a0010)
 */
u_long *GsU_000a0010(GsARGUNIT *sp)
{
	register GsADIV_F4	*ifo;
	register HMD_P_F4	*tp;
	GsARGUNIT_NORMAL	*ap = (GsARGUNIT_NORMAL *)sp;
	SVECTOR			*vp = ap->vertop;
	SVECTOR			*np = ap->nortop;
	GsADIV_P_F4		*p1;
	POLY_F4			*si;
	u_long			*scratch = (u_long *)(ap+1);
	long			*otz;
	u_long			t0;
	u_long			t1;
	u_long			tagmask;
	int			i;
	int			num;

	num = *(ap->primp)>>16;

	ap->primp++;
	tp = (HMD_P_F4 *)(ap->primtop+(*(ap->primp)&0x00ffffff));

	ifo = (GsADIV_F4 *)scratch;
	scratch += sizeof(GsADIV_F4)/4;
	p1 = (GsADIV_P_F4 *)scratch;

	ifo->limit = (u_long)(*(ap->primp)>>24);
	ifo->hwd0 = HWD0/2;
	ifo->vwd0 = VWD0/2;
	ifo->adivz = GsADIVZ;
	ifo->adivw = GsADIVW;
	ifo->adivh = GsADIVH;
	ifo->pk = (u_long *)ap->out_packetp;
	ifo->org = (u_long *)ap->tagp->org;
	ifo->shift = ap->shift;
	setPolyF4(&ifo->si);

	si = (POLY_F4 *)ifo->pk;

	for (i = 0; i < num; i++, tp++) {
		otz = &ifo->otz;
		t1 = 0x00040000;
		t0 = 0x80000000;
		tagmask = 0x00ffffff;

		gte_ldrgb(&tp->r0);
		gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);

		gte_rtpt();
		gte_stflg(&ifo->flg0);
		gte_nclip();
		gte_stopz(otz);

		if (*otz <= 0) {
			continue;
		}

		gte_ldv0(&np[tp->n0]);
		gte_ncds();
		gte_stsxy3_f4((u_long *)si);
		gte_ldv0(&vp[tp->v3]);
		gte_rtps();
		gte_stflg(&ifo->flg);

		if ((ifo->flg & t1) == 0 || (ifo->flg0 & t1) == 0) {
			gte_stsxy((u_long *)si + 5);
			gte_avsz4();
			gte_stotz(otz);
			ifo->tag = (u_long *)(ifo->org + (*otz >> ifo->shift));
			if (*otz < ifo->adivz) {
				goto divide;
			}
			if ((ifo->flg & t0) == 0 || (ifo->flg0 & t0) == 0) {
				*(u_long *)si = (*ifo->tag & tagmask) | 0x05000000;
				*ifo->tag = (u_long)si & tagmask;
				gte_strgb(&si->r0);
				si++;
			} else {
				goto divide;
			}
			continue;
divide:
			gte_strgb(&ifo->si.r0);
			*(SVECTOR *)&p1->vt[0] = vp[tp->v0];
			*(SVECTOR *)&p1->vt[1] = vp[tp->v1];
			*(SVECTOR *)&p1->vt[2] = vp[tp->v2];
			*(SVECTOR *)&p1->vt[3] = vp[tp->v3];
			ifo->pk = (u_long *)si;
			func_00000488(scratch, ifo, 0);
			si = (POLY_F4 *)ifo->pk;
			continue;
		}
	}
	GsOUT_PACKET_P = (PACKET *)si;
	return(ap->primp+1);
}
