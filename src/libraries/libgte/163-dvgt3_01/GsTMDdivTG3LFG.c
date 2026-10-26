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
    u_short p;
    u_short n0, v0;
    u_short n1, v1;
    u_short n2, v2;
} TMD_P_TG3;

extern u_char GsTON;
extern u_long *RCpolyGT3A(u_long *p, DIVPOLYGON3 *divp, long mode, CRVECTOR3 *cr);
extern long RotAverageNclipColorDpq3_1(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
                                       SVECTOR *v3, SVECTOR *v4, SVECTOR *v5,
                                       CVECTOR *v6, long *sxy0, long *sxy1,
                                       long *sxy2, CVECTOR *v7, CVECTOR *v8,
                                       CVECTOR *v9, long *otz, long *flag);

u_long *GsTMDdivTG3LFG(TMD_P_TG3 *primtop, SVECTOR *vertop, SVECTOR *nortop,
                       POLY_GT3 *s, u_long n, u_long shift, GsOT *otp,
                       DIVPOLYGON3 *divp)
{
    register POLY_GT3 *packet = s;
    u_long i;
    u_long rgbc = 0x34808080;
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
    cr[0].r0 = r0;
    cr[0].r1 = r1;
    cr[0].r2 = r2;

    for (i = 0; i < n; i++) {
        r0->v = vertop[primtop->v0];
        r1->v = vertop[primtop->v1];
        r2->v = vertop[primtop->v2];
        if (RotAverageNclipColorDpq3_1((SVECTOR *)r0, (SVECTOR *)r1,
                                       (SVECTOR *)r2,
                                       &nortop[primtop->n0],
                                       &nortop[primtop->n1],
                                       &nortop[primtop->n2],
                                       (CVECTOR *)&rgbc,
                                       (long *)&r0->sxy,
                                       (long *)&r1->sxy,
                                       (long *)&r2->sxy,
                                       &r0->c, &r1->c, &r2->c,
                                       &otz, &flag) > 0) {
            ReadSZfifo3((long *)&r0->sz,
                        (long *)&r1->sz,
                        (long *)&r2->sz);
            divp->ot = &otp->org[((u_short)otz - otp->offset) >> shift];
            divp->rgbc.cd = primtop->cd | (GsTON << 1);
            divp->clut = primtop->clut;
            divp->tpage = primtop->tpage;
            *(u_long *)r0->uv = *(u_long *)&primtop->tu0;
            *(u_long *)r1->uv = *(u_long *)&primtop->tu1;
            *(u_long *)r2->uv = *(u_long *)&primtop->tu2;
            packet = (POLY_GT3 *)RCpolyGT3A((u_long *)packet, divp, 0, cr);
        }
        primtop++;
    }
    return (u_long *)packet;
}
