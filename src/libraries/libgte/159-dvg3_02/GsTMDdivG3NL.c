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
} TMD_P_G3;

extern u_char GsTON;
extern u_long *RCpolyG3A(u_long *p, DIVPOLYGON3 *divp, long mode, CRVECTOR3 *cr);

u_long *GsTMDdivG3NL(TMD_P_G3 *primtop, SVECTOR *vertop, SVECTOR *nortop,
                     POLY_G3 *s, u_long n, u_long shift, GsOT *otp,
                     DIVPOLYGON3 *divp)
{
    u_long i;
    long p;
    long otz;
    long flag;
    RVECTOR *r0;
    RVECTOR *r1;
    RVECTOR *r2;
    CRVECTOR3 *cr;

    r0 = &divp->r0;
    r1 = &divp->r1;
    r2 = &divp->r2;
    cr = divp->cr;

    divp->cr[0].r0 = r0;
    divp->cr[0].r1 = r1;
    divp->cr[0].r2 = r2;

    for (i = 0; i < n; i++) {
        r0->v = vertop[primtop->v0];
        r1->v = vertop[primtop->v1];
        r2->v = vertop[primtop->v2];
        if (RotAverageNclip3((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                             (long *)&r0->sxy, (long *)&r1->sxy,
                             (long *)&r2->sxy,
                             &p, &otz, &flag) > 0) {
            ReadSZfifo3((long *)&r0->sz, (long *)&r1->sz, (long *)&r2->sz);
            divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
            divp->rgbc.cd = primtop->cd | (GsTON << 1);
            *(u_long *)&r0->c = *(u_long *)&primtop->r0;
            *(u_long *)&r1->c = *(u_long *)&primtop->r0;
            *(u_long *)&r2->c = *(u_long *)&primtop->r0;
            s = (POLY_G3 *)RCpolyG3A((u_long *)s, divp, 0, cr);
        }
        primtop++;
    }
    return (u_long *)s;
}
