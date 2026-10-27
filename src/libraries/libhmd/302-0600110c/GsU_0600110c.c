/* Recovered from the supplied Sony SRC/LIB/HMD/0600110C.C (ENVMAP.H). */
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
	u_char  r0, g0, b0, code;
	u_short n0, v0;
	u_short n1, v1;
	u_short n2, v2;
}	HMD_P_G3;

/*
 * Shared Gouraud Triangle -> Shared Flat Texture Triangle
 * for HMD-ENV (1D-ENV for Shared G3)
 */
u_long *GsU_0600110c(GsARGUNIT *sp)
{
	register POLY_FT3	*pp;
	register HMD_P_G3	*tp;
	register int		i, j;
	GsARGUNIT_SHARED	*ap = (GsARGUNIT_SHARED *)sp;
	GsWORKUNIT		*wu = ap->vertop2;
	SVECTOR 		*cv = ap->nortop2;
	MATRIX			m0;
	long			sz;
	int			num;
	u_long			*tag;
	/* added variable */
	VECTOR lv;
	u_short tmpn;
	GsARGUNIT_ENVMAP	*ep = (GsARGUNIT_ENVMAP *)sp;
	u_short			tpage; /* to scratch */
	u_char			material2;

	pp = (POLY_FT3 *)ap->out_packetp;
	num = *(ap->primp)>>16;
	ap->primp++;
	tp = (HMD_P_G3 *)(ap->primtop+(*(ap->primp)));

	tpage = GetTPage(ep->p00, 0, ((u_short *)(ep->tex1))[4],
	                 ((u_short *)(ep->tex1))[5]);
	material2 = ep->p02;

#if 1	/* 1997/10/16 patch */
	/* 1997/10/20 patch */
	tpage = GetTPage(2, 0, 768,0);	/* 16bit,(768,0) */
	material2 = 4;
#endif

	for (i = 0; i < num; i++, tp++) {
		if ((*(u_long *)&(wu[tp->v0].otz) == 0xffffffff) ||
		    (*(u_long *)&(wu[tp->v1].otz) == 0xffffffff) ||
		    (*(u_long *)&(wu[tp->v2].otz) == 0xffffffff)) {
			continue;
		}
		*(u_long *)&(pp->x0) = *(u_long *)&(wu[tp->v0].vec);
		*(u_long *)&(pp->x1) = *(u_long *)&(wu[tp->v1].vec);
		*(u_long *)&(pp->x2) = *(u_long *)&(wu[tp->v2].vec);

		gte_ldsxy3(*(long *)&(pp->x0), *(long *)&(pp->x1),
			   *(long *)&(pp->x2));
		gte_nclip();
		gte_stopz(&sz);
		if (sz <= 0)
			continue;

		gte_ldsz3(wu[tp->v0].otz, wu[tp->v1].otz, wu[tp->v2].otz);
		gte_avsz3();
		gte_stszotz(&sz);

		setPolyFT3(pp);
		setRGB0(pp,0x80,0x80,0x80);	/* default brightness */
		pp->tpage = tpage;

		/* UV calcurate */
		gte_ApplyRotMatrix(&cv[*((u_short *)&(tp->n0)+(0<<1))], &lv);
		pp->u0 = ((int)lv.vy/32+128)&0xff;
		pp->v0 = material2;

		gte_ApplyRotMatrix(&cv[*((u_short *)&(tp->n0)+(1<<1))], &lv);
		pp->u1 = ((int)lv.vy/32+128)&0xff;
		pp->v1 = material2;

		gte_ApplyRotMatrix(&cv[*((u_short *)&(tp->n0)+(2<<1))], &lv);
		pp->u2 = ((int)lv.vy/32+128)&0xff;
		pp->v2 = material2;

		tag = (u_long *)((u_long *)ap->tagp->org +
				((sz - ap->offset) >> ap->shift));
		*(u_long *)pp = (*tag & 0x00ffffff) | 0x07000000;
		*tag = (u_long) pp & 0x00ffffff;
		pp++;
	}
	GsOUT_PACKET_P = (PACKET *)pp;
	return(ap->primp+1);
}
