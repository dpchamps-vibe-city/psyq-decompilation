#include "common.h"
#include <sys/types.h>
#include <libgte.h>

MATRIX *RotMatrix_C(SVECTOR *r, MATRIX *m)
{
    int c0, c1, c2, s0, s1, s2;
    int t0, t1;

    c0 = rcos(r->vx);
    c1 = rcos(r->vy);
    c2 = rcos(r->vz);
    s0 = rsin(r->vx);
    s1 = rsin(r->vy);
    s2 = rsin(r->vz);

    m->m[0][0] = (c2 * c1) >> 12;
    t0 = (c2 * (-s1)) >> 12;
    m->m[1][0] = ((s2 * c0) >> 12) - ((t0 * s0) >> 12);
    m->m[2][0] = ((s2 * s0) >> 12) + ((t0 * c0) >> 12);
    m->m[0][1] = -(s2 * c1) >> 12;
    t1 = (s2 * (-s1)) >> 12;
    m->m[1][1] = ((c2 * c0) >> 12) + ((t1 * s0) >> 12);
    m->m[1][2] = -(c1 * s0) >> 12;
    m->m[2][2] = (c1 * c0) >> 12;
    m->m[2][1] = ((c2 * s0) >> 12) - ((t1 * c0) >> 12);
    m->m[0][2] = s1;

    return m;
}
