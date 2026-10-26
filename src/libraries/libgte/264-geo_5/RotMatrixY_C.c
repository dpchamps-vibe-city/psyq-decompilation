#include "common.h"
#include <sys/types.h>
#include <libgte.h>

MATRIX *RotMatrixY_C(s16 r, MATRIX *m)
{
    int c, s;
    short t[3][3];

    c = rcos(r);
    s = -rsin(r);

    t[0][0] = (c * m->m[0][0] - s * m->m[2][0]) >> 12;
    t[0][1] = (c * m->m[0][1] - s * m->m[2][1]) >> 12;
    t[0][2] = (c * m->m[0][2] - s * m->m[2][2]) >> 12;
    m->m[2][0] = (s * m->m[0][0] + c * m->m[2][0]) >> 12;
    m->m[2][1] = (s * m->m[0][1] + c * m->m[2][1]) >> 12;
    m->m[2][2] = (s * m->m[0][2] + c * m->m[2][2]) >> 12;
    m->m[0][0] = t[0][0];
    m->m[0][1] = t[0][1];
    m->m[0][2] = t[0][2];
    return m;
}
