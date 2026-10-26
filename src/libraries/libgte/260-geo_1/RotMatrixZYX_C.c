#include "common.h"
#include <sys/types.h>
#include <libgte.h>

MATRIX *RotMatrixZYX_C(SVECTOR *r, MATRIX *m) {
    s32 c0;
    s32 c1;
    s32 c2;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 t0;
    s32 t1;

    c0 = rcos(r->vx);
    c1 = rcos(r->vy);
    c2 = rcos(r->vz);
    s0 = rsin(r->vx);
    s1 = rsin(r->vy);
    s2 = rsin(r->vz);

    t0 = (s0 * s1) >> 12;

    m->m[0][0] = (c1 * c2) >> 12;
    m->m[0][1] = ((t0 * c2) >> 12) - ((s2 * c0) >> 12);

    t1 = (s1 * c0) >> 12;

    m->m[0][2] = ((t1 * c2) >> 12) + ((s0 * s2) >> 12);
    m->m[1][0] = (s2 * c1) >> 12;
    m->m[1][1] = ((t0 * s2) >> 12) + ((c0 * c2) >> 12);
    m->m[1][2] = ((t1 * s2) >> 12) - ((s0 * c2) >> 12);
    m->m[2][0] = -s1;
    m->m[2][1] = (s0 * c1) >> 12;
    m->m[2][2] = (c0 * c1) >> 12;
    return m;
}
