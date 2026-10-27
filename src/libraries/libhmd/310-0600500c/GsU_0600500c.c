/* $PSLibId: Run-time Library Release 4.4$ */

/* 
 *	Copyright(C) 1998 Sony Computer Entertainment Inc.
 *  	All rights reserved. 
 */


#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <inline_c.h>
#include <gtemac.h>
#include <asm.h>
#include <libgs.h>
#include <libhmd.h>

/* from ENVMAP.H */
#define SHIFT1 5
#define SHIFT2 1
#define SHIFT3 5
#define SHIFT4 3

typedef struct {
	unsigned long	*primp;
	GsOT		*tagp;
	int		shift;
	int		offset;
	PACKET		*out_packetp;
	unsigned long	*primtop;
	SVECTOR		*vertop;
	SVECTOR		*nortop;
	unsigned long	*tex1;
	unsigned long	*tex2;
	unsigned long	*clut2;
	unsigned long	*tex3;
	unsigned long	*clut3;
	u_char	p00; /* texture mode 0,1,2 */
	u_char	p01;
	u_char	p02; /* material (y offset) */
	u_char	p03;
	u_char	p10; /* texture mode 0,1,2 */
	u_char	p11; /* abr */
	u_char	p12; /* reflect rate */
	u_char	p13;
	u_char	p14;
	u_char	p15;
	u_char	p16;
	u_char	p17;
	u_char	p20; /* texture mode 0,1,2 */
	u_char	p21; /* abr */
	u_char	p22; /* refract rate */
	u_char	p23;
	u_char	p24; 
	u_char	p25; /* r */
	u_char	p26; /* g */
	u_char	p27; /* b */
}	GsARGUNIT_ENVMAP;

typedef struct {
	int     shift;		/* OT shift */
	u_long *org;		/* OT org */
	u_long *pk;		/* packet base */
	long    otz;		/* gte otz */
	long    flg0;		/* gte flag */
	long    flg;		/* gte flag */
	u_long *tag;		/* work temprly for addPrim */
	/* added */
	u_short			tpage_env;
	u_short			clut_env;
	u_short			tpage_org;
	u_short			clut_org;
	u_char			reflect;
	u_char			refract;
}       GsENV;

typedef struct {
	u_char  r0, g0, b0, code;
	u_short n0, v0;
	u_short n1, v1;
	u_short n2, v2;
}	HMD_P_G3;

/*
 * Gouraud Triangle -> Gouraud Texture Triangle
 * for HMD-ENV (2D-ENV (reflection) for G3)
 */
u_long *GsU_0600500c(GsARGUNIT *sp)
{
	register GsENV		*ifo;
	register HMD_P_G3	*tp;
	GsARGUNIT_ENVMAP	*ap = (GsARGUNIT_ENVMAP *)sp;
	SVECTOR			*vp = ap->vertop;
	SVECTOR			*np = ap->nortop;
	u_long			*scratch = (u_long *)(ap+1);
	int			i;
	int			num;
	/* added variable */
	volatile POLY_G3  *si_org;
	volatile POLY_GT3 *si_env;
	GsARGUNIT_ENVMAP	*ep = (GsARGUNIT_ENVMAP *)sp;
	VECTOR lv;
	int uu, vv;
	int ddx, ddy;

	num = *(ap->primp)>>16;
	ap->primp++;
	tp = (HMD_P_G3 *)(ap->primtop+(*(ap->primp)&0x00ffffff));

	/* parameters write to scratch pad (initilaize) */
	ifo = (GsENV *)scratch;
	scratch += sizeof(GsENV)/4;
	ifo->pk = (u_long *)ap->out_packetp;
	ifo->org = (u_long *)ap->tagp->org;
	ifo->shift = ap->shift;

	ifo->tpage_env = GetTPage(ep->p10, ep->p11, ((u_short *)(ep->tex2))[4],
	                    ((u_short *)(ep->tex2))[5]);
	if(ep->p10 != 2) {
		ifo->clut_env = GetClut(((u_short *)(ep->clut2))[4],((u_short *)(ep->clut2))[5]);
	}
	ifo->reflect = ep->p12;

	si_env = (POLY_GT3 *) ifo->pk;
	si_org = (POLY_G3 *) (si_env+1);

	for (i = 0; i < num; i++, tp++) {
		gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
		gte_rtpt();			/* RotTransPers3 */
		gte_stflg(&ifo->flg);
		if (ifo->flg & 0x80000000)
			continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&ifo->otz);	/* back clip */
		if (ifo->otz <= 0)
			continue;
		gte_avsz3();
		gte_stotz(&ifo->otz);
		gte_stsxy3_gt3((u_long *) si_env);
		gte_stsxy3_g3((u_long *) si_org);

/* Original polygon */
		/* Original polygon */
		si_org->code = 0x30;	/* G3, ABE=off, TGE=off */
		gte_ldrgb(&tp->r0);
		gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
		gte_ncct();
		gte_strgb3_g3((u_long *)si_org);

/* Reflection polygon */
		si_env->code = 0x36;	/* GT3, ABE=on, TGE=off */
		si_env->tpage = ifo->tpage_env;
		if(ep->p10 != 2) si_env->clut = ifo->clut_env;

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[tp->n0], &lv);   /* normal->screen coord */
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x0>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y0>>SHIFT4)+ddy;
		if(uu < 0)   uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0)   vv = 0;
		if(vv > 255) vv = 255;
		si_env->u0 = uu;
		si_env->v0 = vv;
		si_env->r0 = ifo->reflect;
		si_env->g0 = ifo->reflect;
		si_env->b0 = ifo->reflect;

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[tp->n1], &lv);   /* normal->screen coord */
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x1>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y1>>SHIFT4)+ddy;
		if(uu < 0)   uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0)   vv = 0;
		if(vv > 255) vv = 255;
		si_env->u1 = uu;
		si_env->v1 = vv;
		si_env->r1 = ifo->reflect;
		si_env->g1 = ifo->reflect;
		si_env->b1 = ifo->reflect;

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[tp->n2], &lv);   /* normal->screen coord */
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x2>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y2>>SHIFT4)+ddy;
		if(uu < 0)   uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0)   vv = 0;
		if(vv > 255) vv = 255;
		si_env->u2 = uu;
		si_env->v2 = vv;
		si_env->r2 = ifo->reflect;
		si_env->g2 = ifo->reflect;
		si_env->b2 = ifo->reflect;

		ifo->tag = (u_long *) (ifo->org + (ifo->otz >> ifo->shift));
		*(u_long *) si_env = (u_long)((*ifo->tag & 0x00ffffff) | 0x09000000);
		*ifo->tag = (u_long) si_env & 0x00ffffff;
		ifo->tag = (u_long *) (ifo->org + (ifo->otz >> ifo->shift));
		*(u_long *) si_org = (u_long)((*ifo->tag & 0x00ffffff) | 0x06000000);
		*ifo->tag = (u_long) si_org & 0x00ffffff;
		si_env = (POLY_GT3 *) (si_org+1);
		si_org = (POLY_G3 *) (si_env+1);
	}

	GsOUT_PACKET_P = (PACKET *)si_env;
	return(ap->primp+1);
}
