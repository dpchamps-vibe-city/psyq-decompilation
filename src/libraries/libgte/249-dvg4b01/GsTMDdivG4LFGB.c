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
    u_char r0, g0, b0, code;
    u_short n0, v0;
    u_short n1, v1;
    u_short n2, v2;
    u_short n3, v3;
} TMD_P_G4;

extern u_char GsTON;
extern u_long *RCpolyG4A(u_long *p, DIVPOLYGON4 *divp, long mode, CRVECTOR4 *cr);

u_long *GsTMDdivG4LFGB(TMD_P_G4 *primtop, SVECTOR *vertop, SVECTOR *nortop,
                       POLY_G4 *s, u_long n, u_long shift, GsOT *otp,
                       DIVPOLYGON4 *divp)
{
    u_long i;
    long otz;
    long oz;
    long flag;
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
        oz = RotAverage4((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                         (SVECTOR *)r3,
                         (long *)&r0->sxy, (long *)&r1->sxy,
                         (long *)&r2->sxy, (long *)&r3->sxy,
                         &otz, &flag);
        ReadSZfifo4((long *)&r0->sz, (long *)&r1->sz,
                    (long *)&r2->sz, (long *)&r3->sz);
        NormalColorDpq3(&nortop[primtop->n0], &nortop[primtop->n1],
                        &nortop[primtop->n2], (CVECTOR *)&primtop->r0, otz,
                        &r0->c, &r1->c, &r2->c);
        NormalColorDpq(&nortop[primtop->n3], (CVECTOR *)&primtop->r0, otz,
                       &r3->c);
        divp->ot = &otp->org[((u_short)oz - otp->offset) >> shift];
        divp->rgbc.cd = primtop->cd | (GsTON << 1);
        s = (POLY_G4 *)RCpolyG4A((u_long *)s, divp, 0, cr);
        primtop++;
    }
    return (u_long *)s;
}
