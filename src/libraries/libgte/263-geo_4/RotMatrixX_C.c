#include "common.h"
#include <sys/types.h>
#include <libgte.h>

MATRIX *RotMatrixX_C(s16 r, MATRIX *m)
{
    s32 c, s;
    s16 t[3][3];

    c = rcos(r);
    s = rsin(r);
    t[1][0] = (c * m->m[1][0] - s * m->m[2][0]) >> 12;
    t[1][1] = (c * m->m[1][1] - s * m->m[2][1]) >> 12;
    t[1][2] = (c * m->m[1][2] - s * m->m[2][2]) >> 12;
    m->m[2][0] = (s * m->m[1][0] + c * m->m[2][0]) >> 12;
    m->m[2][1] = (s * m->m[1][1] + c * m->m[2][1]) >> 12;
    m->m[2][2] = (s * m->m[1][2] + c * m->m[2][2]) >> 12;
    m->m[1][0] = t[1][0];
    m->m[1][1] = t[1][1];
    m->m[1][2] = t[1][2];
    return m;
}
