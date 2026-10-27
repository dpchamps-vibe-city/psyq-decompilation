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
	u_short n3, v3;
}	HMD_P_G4;

/*
 * Gouraud Quad -> Flat Texture Quad
 * for HMD-ENV (1D-ENV for G4)
 */
u_long *GsU_06001014(GsARGUNIT *sp)
{
	register GsENV		*ifo;
	register HMD_P_G4	*tp;
	GsARGUNIT_ENVMAP	*ap = (GsARGUNIT_ENVMAP *)sp;
	SVECTOR			*vp = ap->vertop;
	SVECTOR			*np = ap->nortop;
	u_long			*scratch = (u_long *)(ap+1);
	int			i;
	int			num;
	/* added variable */
	volatile POLY_FT4 *si_env;
	VECTOR lv;
	GsARGUNIT_ENVMAP	*ep = (GsARGUNIT_ENVMAP *)sp;
	u_short			tpage; /* to scratch */
	u_char			material2;

	num = *(ap->primp)>>16;
	ap->primp++;
	tp = (HMD_P_G4 *)(ap->primtop+(*(ap->primp)&0x00ffffff));

	tpage = GetTPage(ep->p00, 0, ((u_short *)(ep->tex1))[4],
	                 ((u_short *)(ep->tex1))[5]);
	material2 = ep->p02;

	/* parameters write to scratch pad (initilaize) */
	ifo = (GsENV *)scratch;
	scratch += sizeof(GsENV)/4;
	ifo->pk = (u_long *)ap->out_packetp;
	ifo->org = (u_long *)ap->tagp->org;
	ifo->shift = ap->shift;

	si_env = (POLY_FT4 *) ifo->pk;

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

		gte_stsxy3_ft4((u_long *) si_env);
		gte_ldv0(&vp[tp->v3]);
		gte_rtps();
		gte_stflg(&ifo->flg);
		if ((ifo->flg & 0x00040000) && (ifo->flg0 & 0x00040000)) {
			continue;
		}
		gte_stsxy((u_long *)&si_env->x3);
		gte_avsz4();
		gte_stotz(&ifo->otz);

		setPolyFT4(si_env);
		setRGB0(si_env,0x80,0x80,0x80);	/* default brightness */
		si_env->tpage = tpage;

		/* UV calcurate */
		gte_ApplyRotMatrix(&np[tp->n0], &lv);
		si_env->u0 = ((int)lv.vy/32+128)&0xff;
		si_env->v0 = material2;

		gte_ApplyRotMatrix(&np[tp->n1], &lv);
		si_env->u1 = ((int)lv.vy/32+128)&0xff;
		si_env->v1 = material2;

		gte_ApplyRotMatrix(&np[tp->n2], &lv);
		si_env->u2 = ((int)lv.vy/32+128)&0xff;
		si_env->v2 = material2;

		gte_ApplyRotMatrix(&np[tp->n3], &lv);
		si_env->u3 = ((int)lv.vy/32+128)&0xff;
		si_env->v3 = material2;

		ifo->tag = (u_long *) (ifo->org + (ifo->otz >> ifo->shift));
		*(u_long *) si_env = (u_long)((*ifo->tag & 0x00ffffff) | 0x09000000);
		*ifo->tag = (u_long) si_env & 0x00ffffff;
		si_env++;
	}

	GsOUT_PACKET_P = (PACKET *)si_env;
	return(ap->primp+1);
}
