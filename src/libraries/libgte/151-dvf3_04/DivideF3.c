#include "common.h"
#include <sys/types.h>

#include <libgte.h>
#include <libgpu.h>

extern u_long *RCpolyF3A(u_long *p, DIVPOLYGON3 *divp, long mode, CRVECTOR3 *cr);

u_long *DivideF3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, CVECTOR *rgbc,
                 POLY_F3 *s, u_long *ot, DIVPOLYGON3 *divp)
{
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

    r0->v = *v0;
    r1->v = *v1;
    r2->v = *v2;

    if (RotAverageNclip3((SVECTOR *)r0, (SVECTOR *)r1, (SVECTOR *)r2,
                         (long *)&r0->sxy, (long *)&r1->sxy, (long *)&r2->sxy,
                         &p, &otz, &flag) > 0) {
        ReadSZfifo3((long *)&r0->sz, (long *)&r1->sz, (long *)&r2->sz);
        divp->ot = ot;
        divp->rgbc = *rgbc;
        s = (POLY_F3 *)RCpolyF3A((u_long *)s, divp, 0, cr);
    }
    return (u_long *)s;
}
