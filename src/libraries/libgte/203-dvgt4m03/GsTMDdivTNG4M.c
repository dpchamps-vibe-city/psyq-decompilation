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
    u_char r0, g0, b0, p2;
    u_char r1, g1, b1, p3;
    u_char r2, g2, b2, p4;
    u_char r3, g3, b3, p5;
    u_short v0, v1;
    u_short v2, v3;
} TMD_P_TNG4;

extern u_char GsTON;
extern u_long *RCpolyGT4A(u_long *p, DIVPOLYGON4 *divp, long mode, CRVECTOR4 *cr);

u_long *GsTMDdivTNG4M(TMD_P_TNG4 *primtop, SVECTOR *vertop,
                      POLY_GT4 *s, u_long n, u_long shift, GsOT *otp,
                      DIVPOLYGON4 *divp)
{
    long i;
    long otz;
    long flag;
    long p;
    long nclip;
    RVECTOR *r0;
    RVECTOR *r1;
    RVECTOR *r2;
    RVECTOR *r3;
    CRVECTOR4 *cr;
    long u0;
    long v0;
    long u3;
    long v3;
    long uw;
    long vh;
    long nu0;
    long nv0;
    long midv;
    long u0w;
    long du;
    long dv;

    r0 = &divp->r0;
    r1 = &divp->r1;
    r2 = &divp->r2;
    r3 = &divp->r3;
    cr = divp->cr;

    divp->cr[0].r0 = r0;
    divp->cr[0].r1 = r1;
    divp->cr[0].r2 = r2;
    divp->cr[0].r3 = r3;

    i = 0;
    if (n != 0) {
        do {
            r0->v = vertop[primtop->v0];
            r1->v = vertop[primtop->v1];
            r2->v = vertop[primtop->v2];
            r3->v = vertop[primtop->v3];
            nclip = RotAverageNclip4((SVECTOR *)r0, (SVECTOR *)r1,
                                     (SVECTOR *)r2, (SVECTOR *)r3,
                                     (long *)&r0->sxy, (long *)&r1->sxy,
                                     (long *)&r2->sxy, (long *)&r3->sxy,
                                     &p, &otz, &flag);
            if (nclip > 0) {
                ReadSZfifo4((long *)&r0->sz, (long *)&r1->sz,
                            (long *)&r2->sz, (long *)&r3->sz);
                divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
                divp->rgbc.cd = (GsTON << 1) | (primtop->cd & 0xFE);
                divp->clut = primtop->clut;
                divp->tpage = primtop->tpage;
                *(u_long *)&r0->c = *(u_long *)&primtop->r0;
                *(u_long *)&r1->c = *(u_long *)&primtop->r1;
                *(u_long *)&r2->c = *(u_long *)&primtop->r2;
                *(u_long *)&r3->c = *(u_long *)&primtop->r3;
                u0 = primtop->tu0;
                v0 = primtop->tv0;
                u3 = primtop->tu3;
                v3 = primtop->tv3;
                uw = (u3 - u0 + 1) & 0xFFFE;
                vh = (v3 - v0 + 1) & 0xFFFE;
                u0w = u0 + uw;
                if (nclip < (uw * vh) >> 6) {
                    nu0 = u0w + (uw >> 3);
                    midv = v0 + (vh >> 1);
                    nv0 = midv + (vh >> 3);
                    du = (uw >> 3) - 1;
                    dv = (vh >> 3) - 1;
                    *(u_long *)r0->uv = nu0 | (nv0 << 8);
                    *(u_long *)r1->uv = (nu0 + du) | (nv0 << 8);
                    *(u_long *)r2->uv = nu0 | ((nv0 + dv) << 8);
                    *(u_long *)r3->uv = (nu0 + du) | ((nv0 + dv) << 8);
                } else if (nclip < (uw * vh) >> 4) {
                    nu0 = u0w + (uw >> 2);
                    nv0 = v0 + (vh >> 1);
                    du = (uw >> 2) - 1;
                    dv = (vh >> 2) - 1;
                    *(u_long *)r0->uv = nu0 | (nv0 << 8);
                    *(u_long *)r1->uv = (nu0 + du) | (nv0 << 8);
                    *(u_long *)r2->uv = nu0 | ((nv0 + dv) << 8);
                    *(u_long *)r3->uv = (nu0 + du) | ((nv0 + dv) << 8);
                } else if (nclip < (uw * vh) >> 2) {
                    du = (uw >> 1) - 1;
                    dv = (vh >> 1) - 1;
                    *(u_long *)r0->uv = u0w | (v0 << 8);
                    *(u_long *)r1->uv = (u0w + du) | (v0 << 8);
                    *(u_long *)r2->uv = u0w | ((v0 + dv) << 8);
                    *(u_long *)r3->uv = (u0w + du) | ((v0 + dv) << 8);
                } else {
                    *(u_long *)r0->uv = *(u_long *)&primtop->tu0;
                    *(u_long *)r1->uv = *(u_long *)&primtop->tu1;
                    *(u_long *)r2->uv = *(u_long *)&primtop->tu2;
                    *(u_long *)r3->uv = *(u_long *)&primtop->tu3;
                }
                s = (POLY_GT4 *)RCpolyGT4A((u_long *)s, divp, 0, cr);
            }
            primtop++;
            i++;
        } while (i < n);
    }
    return (u_long *)s;
}
