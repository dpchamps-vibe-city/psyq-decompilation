#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
	u_char	r0, g0, b0, code;
	u_char	r1, g1, b1, pad1;
	u_char	r2, g2, b2, pad2;
	u_char	r3, g3, b3, pad3;
	u_short v0, v1, v2, v3;
}       HMD_P_NG4;

extern u_long *RCpolyG4A(u_long *p, DIVPOLYGON4 *divp, long mode, CRVECTOR4 *cr);

/*
 * Divide Non-light Gouraud Quad (GsUDNG4)
 */
u_long *GsU_00050054(GsARGUNIT *sp)
{
	GsARGUNIT_NORMAL	*ap = (GsARGUNIT_NORMAL *)sp;
	POLY_G4			*pp;
	HMD_P_NG4		*tp;
	DIVPOLYGON4		*divp = (DIVPOLYGON4 *)(&(ap->nortop)+1);
	RVECTOR			*r0, *r1, *r2, *r3;
	SVECTOR			*vp = ap->vertop;
	int			i;
	long			sz;
	long			p, flag;
	CRVECTOR4		*crv;
	long			lv;
	int			num;

	pp = (POLY_G4 *)ap->out_packetp;
	num = *(ap->primp)>>16;

	ap->primp++;
	tp = (HMD_P_NG4 *)(ap->primtop+(*(ap->primp)&0x00ffffff));

	divp->ndiv = *(ap->primp)>>24;
	divp->pih = HWD0;
	divp->piv = VWD0;

	r0= &divp->r0;
	r1= &divp->r1;
	r2= &divp->r2;
	r3= &divp->r3;
	lv=0;
	crv = divp->cr;
	divp->cr[lv].r0 = r0;
	divp->cr[lv].r1 = r1;
	divp->cr[lv].r2 = r2;
	divp->cr[lv].r3 = r3;

	for (i = 0; i < num; i++, tp++) {
		r0->v = *(vp + tp->v0);
		r1->v = *(vp + tp->v1);
		r2->v = *(vp + tp->v2);
		r3->v = *(vp + tp->v3);
		if (RotAverageNclip4(&r0->v, &r1->v, &r2->v, &r3->v,
		    (long *)&r0->sxy, (long *)&r1->sxy,
		    (long *)&r2->sxy, (long *)&r3->sxy,
		    &p, &sz, &flag) > 0) {
			ReadSZfifo4(&r0->sz, &r1->sz, &r2->sz, &r3->sz);
			divp->ot = (u_long *)(ap->tagp->org +
			    (((u_short)sz - ap->offset) >> ap->shift));
			divp->rgbc.cd = tp->code;
			*(u_long *)&r0->c = *(u_long *)(&tp->r0);
			*(u_long *)&r1->c = *(u_long *)(&tp->r1);
			*(u_long *)&r2->c = *(u_long *)(&tp->r2);
			*(u_long *)&r3->c = *(u_long *)(&tp->r3);
			pp = (POLY_G4 *)RCpolyG4A((u_long *)pp, divp, lv, crv);
		}
	}
	GsOUT_PACKET_P = (PACKET *)pp;
	return(ap->primp+1);
}
