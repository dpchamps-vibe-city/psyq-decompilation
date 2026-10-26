#include "common.h"
#include <sys/types.h>

#include <libgte.h>
#include <libgpu.h>

extern u_long *RCpolyFT4A(u_long *p, DIVPOLYGON4 *divp, long mode, CRVECTOR4 *cr);

u_long *DivideFT4(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3,
                  u_long *p0, u_long *p1, u_long *p2, u_long *p3,
                  CVECTOR *rgbc, u_long *p, u_long *ot, DIVPOLYGON4 *divp)
{
    long pih;
    long otz;
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

    r0->v = *v0;
    r1->v = *v1;
    r2->v = *v2;
    r3->v = *v3;

    if (RotAverageNclip4((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                         (SVECTOR *)r3,
                         (long *)&r0->sxy, (long *)&r1->sxy,
                         (long *)&r2->sxy, (long *)&r3->sxy,
                         &pih, &otz, &flag) > 0) {
        ReadSZfifo4((long *)&r0->sz, (long *)&r1->sz,
                    (long *)&r2->sz, (long *)&r3->sz);
        divp->ot = ot;
        divp->rgbc = *rgbc;
        divp->clut = *(u_short *)((u_char *)p0 + 2);
        divp->tpage = *(u_short *)((u_char *)p1 + 2);
        *(u_long *)r0->uv = *p0;
        *(u_long *)r1->uv = *p1;
        *(u_long *)r2->uv = *p2;
        *(u_long *)r3->uv = *p3;
        p = (u_long *)RCpolyFT4A((u_long *)p, divp, 0, cr);
    }
    return p;
}
