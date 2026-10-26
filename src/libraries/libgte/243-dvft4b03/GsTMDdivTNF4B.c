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
    u_short pad;
    u_char tu3, tv3;
    u_short pad1;
    u_char r0, g0, b0, p2;
    u_short v0, v1;
    u_short v2, v3;
} TMD_P_TNF4;

extern u_char GsTON;
extern u_long *RCpolyFT4A(u_long *p, DIVPOLYGON4 *divp, long mode, CRVECTOR4 *cr);

u_long *GsTMDdivTNF4B(TMD_P_TNF4 *primtop, SVECTOR *vertop,
                      POLY_FT4 *s, u_long n, u_long shift, GsOT *otp,
                      DIVPOLYGON4 *divp)
{
    u_long i;
    u_short otz;
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
        otz = RotAverage4((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                          (SVECTOR *)r3, (long *)&r0->sxy, (long *)&r1->sxy,
                          (long *)&r2->sxy, (long *)&r3->sxy, &p, &flag);
        ReadSZfifo4((long *)&r0->sz, (long *)&r1->sz, (long *)&r2->sz,
                    (long *)&r3->sz);
        divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
        *(u_long *)&divp->rgbc = *(u_long *)&primtop->r0;
        divp->rgbc.cd = (GsTON << 1) | (primtop->cd & 0xFE);
        divp->clut = primtop->clut;
        divp->tpage = primtop->tpage;
        *(u_long *)r0->uv = *(u_long *)&primtop->tu0;
        *(u_long *)r1->uv = *(u_long *)&primtop->tu1;
        *(u_long *)r2->uv = *(u_long *)&primtop->tu2;
        *(u_long *)r3->uv = *(u_long *)&primtop->tu3;
        s = (POLY_FT4 *)RCpolyFT4A((u_long *)s, divp, 0, cr);
        primtop++;
    }
    return (u_long *)s;
}
