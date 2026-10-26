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
    u_short n0, v0;
    u_short v1, v2;
} TMD_P_TF3;

extern u_char GsTON;
extern u_long *RCpolyFT3A(u_long *p, DIVPOLYGON3 *divp, long mode, CRVECTOR3 *cr);

u_long *GsTMDdivTF3L(TMD_P_TF3 *primtop, SVECTOR *vertop, SVECTOR *nortop,
                     POLY_FT3 *s, u_long n, u_long shift, GsOT *otp,
                     DIVPOLYGON3 *divp)
{
    register POLY_FT3 *packet = s;
    u_long i;
    u_long rgbc = 0x24808080;
    u_short otz;
    long flag;
    long p;
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

    i = 0;
    if (n != 0) {
        long *sxy1 = (long *)&divp->r1.sxy;
        long *sxy2 = (long *)&divp->r2.sxy;
        CVECTOR *c0 = &divp->rgbc;
        CVECTOR *c1 = &divp->r1.c;
        CVECTOR *c2 = &divp->r2.c;
        do {
        r0->v = vertop[primtop->v0];
        r1->v = vertop[primtop->v1];
        r2->v = vertop[primtop->v2];
        if (!(primtop->dummy & 2)) {
            if (RotAverageNclipColorCol3((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                                         &nortop[primtop->n0],
                                         &nortop[primtop->n0],
                                         &nortop[primtop->n0],
                                         (CVECTOR *)&rgbc,
                                         (long *)&r0->sxy,
                                         sxy1, sxy2,
                                         c0, c1, c2,
                                         (long *)&otz, &flag) > 0) {
                ReadSZfifo3((long *)&r0->sz, (long *)&r1->sz, (long *)&r2->sz);
                divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
                divp->rgbc.cd = primtop->cd | (GsTON << 1);
                divp->clut = primtop->clut;
                divp->tpage = primtop->tpage;
                *(u_long *)r0->uv = *(u_long *)&primtop->tu0;
                *(u_long *)r1->uv = *(u_long *)&primtop->tu1;
                *(u_long *)r2->uv = *(u_long *)&primtop->tu2;
                packet = (POLY_FT3 *)RCpolyFT3A((u_long *)packet, divp, 0, cr);
            }
        } else {
            long *flagp = &flag;
            otz = RotAverage3((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                              (long *)&r0->sxy, sxy1,
                              sxy2, &p, flagp);
            NormalColorCol3(&nortop[primtop->n0], &nortop[primtop->n0],
                             &nortop[primtop->n0], (CVECTOR *)&rgbc,
                             c0, c1, c2);
        ReadSZfifo3((long *)&r0->sz, (long *)&r1->sz, (long *)&r2->sz);
        divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
        divp->rgbc.cd = primtop->cd | (GsTON << 1);
        divp->clut = primtop->clut;
        divp->tpage = primtop->tpage;
        *(u_long *)r0->uv = *(u_long *)&primtop->tu0;
        *(u_long *)r1->uv = *(u_long *)&primtop->tu1;
        *(u_long *)r2->uv = *(u_long *)&primtop->tu2;
        packet = (POLY_FT3 *)RCpolyFT3A((u_long *)packet, divp, 0, cr);
        }
        primtop++;
        i++;
        } while (i < n);
    }
    return (u_long *)packet;
}
