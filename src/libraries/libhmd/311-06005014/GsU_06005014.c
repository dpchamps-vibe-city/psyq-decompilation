/* Recovered from the supplied Sony SRC/LIB/HMD/06005014.C (ENVMAP.H). */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <inline_c.h>
#include <gtemac.h>
#include <asm.h>
#include <libgs.h>
#include <libhmd.h>

/* from ENVMAP.H */
#define SHIFT3 5
#define SHIFT4 3

typedef struct {
	unsigned long *primp;
	GsOT *tagp;
	int shift;
	int offset;
	PACKET *out_packetp;
	unsigned long *primtop;
	SVECTOR *vertop;
	SVECTOR *nortop;
	unsigned long *tex1;
	unsigned long *tex2;
	unsigned long *clut2;
	unsigned long *tex3;
	unsigned long *clut3;
	u_char p00, p01, p02, p03;
	u_char p10, p11, p12, p13, p14, p15, p16, p17;
	u_char p20, p21, p22, p23, p24, p25, p26, p27;
} GsARGUNIT_ENVMAP;

typedef struct {
	int shift;
	u_long *org;
	u_long *pk;
	long otz;
	long flg0;
	long flg;
	u_long *tag;
	u_short tpage_env;
	u_short clut_env;
	u_short tpage_org;
	u_short clut_org;
	u_char reflect;
	u_char refract;
} GsENV;

typedef struct {
	u_char r0, g0, b0, code;
	u_short n0, v0;
	u_short n1, v1;
	u_short n2, v2;
	u_short n3, v3;
} HMD_P_G4;

/* Gouraud Quad -> Gouraud Texture Quad, 2D environment reflection. */
u_long *GsU_06005014(GsARGUNIT *sp)
{
	register GsENV *ifo;
	register HMD_P_G4 *tp;
	GsARGUNIT_ENVMAP *ap = (GsARGUNIT_ENVMAP *)sp;
	SVECTOR *vp = ap->vertop;
	SVECTOR *np = ap->nortop;
	u_long *scratch = (u_long *)(ap+1);
	int i;
	int num;
	volatile POLY_G4 *si_org;
	volatile POLY_GT4 *si_env;
	VECTOR lv;
	int uu, vv;
	int ddx, ddy;
	unsigned int clip_mask;
	long *flagp;
	long *otzp;

	num = *(ap->primp)>>16;
	ap->primp++;
	tp = (HMD_P_G4 *)(ap->primtop+(*(ap->primp)&0x00ffffff));

	ifo = (GsENV *)scratch;
	scratch += sizeof(GsENV)/4;
	ifo->pk = (u_long *)ap->out_packetp;
	ifo->org = (u_long *)ap->tagp->org;
	ifo->shift = ap->shift;

	ifo->tpage_env = GetTPage(ap->p10, ap->p11, ((u_short *)(ap->tex2))[4],
	                    ((u_short *)(ap->tex2))[5]);
	if(ap->p10 != 2) {
		ifo->clut_env = GetClut(((u_short *)(ap->clut2))[4],((u_short *)(ap->clut2))[5]);
	}
	ifo->reflect = ap->p12;

	si_env = (POLY_GT4 *) ifo->pk;
	si_org = (POLY_G4 *) (si_env+1);

	for (i = 0; i < num; i++, tp++) {
		flagp = &ifo->flg;
		otzp = &ifo->otz;
		clip_mask = 0x00040000;
		gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
		gte_rtpt();
		gte_stflg(flagp);
		if (ifo->flg & 0x80000000)
			continue;
		gte_nclip();
		gte_stopz(otzp);
		if (ifo->otz <= 0)
			continue;
		gte_stsxy3_gt4((u_long *) si_env);
		gte_stsxy3_g3((u_long *) si_org);
		gte_ldv0(&vp[tp->v3]);
		gte_rtps();
		gte_stflg(flagp);
		if ((ifo->flg & clip_mask) && (ifo->flg0 & clip_mask)) {
			continue;
		}
		gte_stsxy((u_long *)&si_env->x3);
		gte_stsxy((u_long *)&si_org->x3);
		gte_avsz4();
		gte_stotz(otzp);

		/* Original polygon. */
		si_org->code = 0x38;
		gte_ldrgb(&tp->r0);
		gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
		gte_ncct();
		gte_strgb3_g4((u_long *)si_org);
		gte_ldv0(&np[tp->n3]);
		gte_nccs();
		gte_strgb(&si_org->r3);

		/* Reflection polygon. */
		si_env->code = 0x3e;
		si_env->tpage = ifo->tpage_env;
		if(ap->p10 != 2) si_env->clut = ifo->clut_env;

		/* First vertex. */
		gte_ApplyRotMatrix(&np[tp->n0], &lv);
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x0>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y0>>SHIFT4)+ddy;
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env->u0 = uu;
		si_env->v0 = vv;
		si_env->r0 = ifo->reflect;
		si_env->g0 = ifo->reflect;
		si_env->b0 = ifo->reflect;

		/* Second vertex. */
		gte_ApplyRotMatrix(&np[tp->n1], &lv);
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x1>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y1>>SHIFT4)+ddy;
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env->u1 = uu;
		si_env->v1 = vv;
		si_env->r1 = ifo->reflect;
		si_env->g1 = ifo->reflect;
		si_env->b1 = ifo->reflect;

		/* Third vertex. */
		gte_ApplyRotMatrix(&np[tp->n2], &lv);
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x2>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y2>>SHIFT4)+ddy;
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env->u2 = uu;
		si_env->v2 = vv;
		si_env->r2 = ifo->reflect;
		si_env->g2 = ifo->reflect;
		si_env->b2 = ifo->reflect;

		/* Fourth vertex. */
		gte_ApplyRotMatrix(&np[tp->n3], &lv);
		ddx = (int)lv.vx>>SHIFT3;
		ddy = (int)lv.vy>>SHIFT3;
		uu = 128-((int)si_env->x3>>SHIFT4)+ddx;
		vv = 128+((int)si_env->y3>>SHIFT4)+ddy;
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env->u3 = uu;
		si_env->v3 = vv;
		si_env->r3 = ifo->reflect;
		si_env->g3 = ifo->reflect;
		si_env->b3 = ifo->reflect;

		ifo->tag = (u_long *) (ifo->org + (ifo->otz >> ifo->shift));
		*(u_long *) si_env = (u_long)((*ifo->tag & 0x00ffffff) | 0x0C000000);
		*ifo->tag = (u_long) si_env & 0x00ffffff;
		ifo->tag = (u_long *) (ifo->org + (ifo->otz >> ifo->shift));
		*(u_long *) si_org = (u_long)((*ifo->tag & 0x00ffffff) | 0x08000000);
		*ifo->tag = (u_long) si_org & 0x00ffffff;

		si_env = (POLY_GT4 *) (si_org+1);
		si_org = (POLY_G4 *) (si_env+1);
	}

	GsOUT_PACKET_P = (PACKET *)si_env;
	return(ap->primp+1);
}
