#include "common.h"
#include <sys/types.h>
#include <libgte.h>

MATRIX *RotMatrixZ_C(short r, MATRIX *m)
{
    int c, s;
    short t[3][3];

    c = rcos(r);
    s = rsin(r);

    t[0][0] = (c * m->m[0][0] - s * m->m[1][0]) >> 12;
    t[0][1] = (c * m->m[0][1] - s * m->m[1][1]) >> 12;
    t[0][2] = (c * m->m[0][2] - s * m->m[1][2]) >> 12;

    m->m[1][0] = (s * m->m[0][0] + c * m->m[1][0]) >> 12;
    m->m[1][1] = (s * m->m[0][1] + c * m->m[1][1]) >> 12;
    m->m[1][2] = (s * m->m[0][2] + c * m->m[1][2]) >> 12;

    m->m[0][0] = t[0][0];
    m->m[0][1] = t[0][1];
    m->m[0][2] = t[0][2];

    return m;
}
