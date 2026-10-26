#include "common.h"
#include <sys/types.h>

typedef struct {
    unsigned long length;
    u_long *org;
    unsigned long offset;
    unsigned long point;
    u_long *tag;
} GsOT;

#include <libgte.h>
#include <libgpu.h>

typedef struct {
    u_char out, in, dummy, cd;
    u_char tu0, tv0;
    u_short clut;
    u_char tu1, tv1;
    u_short tpage;
    u_char tu2, tv2;
    u_short p0;
    u_char tu3, tv3;
    u_short p1;
    u_short n0, v0;
    u_short n1, v1;
    u_short n2, v2;
    u_short n3, v3;
} TMD_P_TG4;

extern u_char GsTON;
extern u_long *RCpolyGT4A(u_long *p, DIVPOLYGON4 *divp, long mode, CRVECTOR4 *cr);
extern long RotAverageNclipColorDpq3_1(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
                                       SVECTOR *v3, SVECTOR *v4, SVECTOR *v5,
                                       CVECTOR *v6, long *sxy0, long *sxy1,
                                       long *sxy2, CVECTOR *v7, CVECTOR *v8,
                                       CVECTOR *v9, long *otz, long *flag);

u_long *GsTMDdivTG4LFG(TMD_P_TG4 *primtop, SVECTOR *vertop, SVECTOR *nortop,
                       POLY_GT4 *s, u_long n, u_long shift, GsOT *otp,
                       DIVPOLYGON4 *divp)
{
    u_long i;
    u_long rgbc = 0x3C808080;
    long otz;
    long flag;
    long p;
    RVECTOR *r0;
    RVECTOR *r1;
    RVECTOR *r2;
    RVECTOR *r3;
    CRVECTOR4 *cr;

    r0 = &divp->r0;
    r1 = &divp->r1;
    r2 = &divp->r2;
    r3 = &divp->r3;
    cr = divp->cr;

    divp->cr[0].r0 = r0;
    divp->cr[0].r1 = r1;
    divp->cr[0].r2 = r2;
    divp->cr[0].r3 = r3;

    for (i = 0; i < n; i++) {
        r0->v = vertop[primtop->v0];
        r1->v = vertop[primtop->v1];
        r2->v = vertop[primtop->v2];
        r3->v = vertop[primtop->v3];
        if (RotAverageNclipColorDpq3_1((SVECTOR *)r0, (SVECTOR *)r1,
                                       (SVECTOR *)r2,
                                       &nortop[primtop->n0],
                                       &nortop[primtop->n1],
                                       &nortop[primtop->n2],
                                       (CVECTOR *)&rgbc,
                                       (long *)&r0->sxy,
                                       (long *)&r1->sxy,
                                       (long *)&r2->sxy,
                                       (CVECTOR *)&r0->c, (CVECTOR *)&r1->c,
                                       (CVECTOR *)&r2->c,
                                       &otz, &flag) > 0) {
            RotTransPers((SVECTOR *)r3, (long *)&r3->sxy, &p, &flag);
            ReadSZfifo4((long *)&r0->sz, (long *)&r1->sz,
                        (long *)&r2->sz, (long *)&r3->sz);
            NormalColorDpq(&nortop[primtop->n3], (CVECTOR *)&rgbc, p,
                           (CVECTOR *)&r3->c);
            divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
            divp->rgbc.cd = primtop->cd | (GsTON << 1);
            divp->clut = primtop->clut;
            divp->tpage = primtop->tpage;
            *(u_long *)r0->uv = *(u_long *)&primtop->tu0;
            *(u_long *)r1->uv = *(u_long *)&primtop->tu1;
            *(u_long *)r2->uv = *(u_long *)&primtop->tu2;
            *(u_long *)r3->uv = *(u_long *)&primtop->tu3;
            s = (POLY_GT4 *)RCpolyGT4A((u_long *)s, divp, 0, cr);
        }
        primtop++;
    }
    return (u_long *)s;
}
