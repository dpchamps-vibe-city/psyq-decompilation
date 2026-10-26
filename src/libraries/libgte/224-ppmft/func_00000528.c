#include "common.h"
#include <sys/types.h>
#include <libgte.h>

static void func_00000528(DVECTOR *v, int *out)
{
    int t;

    if (v[0].vy == v[1].vy)
        t = 0x7FFFFFFF;
    else
        t = ((v[1].vx - v[0].vx) << 12) / (v[1].vy - v[0].vy);
    out[0] = t;

    if (v[1].vy == v[2].vy)
        t = 0x7FFFFFFF;
    else
        t = ((v[2].vx - v[1].vx) << 12) / (v[2].vy - v[1].vy);
    out[1] = t;

    if (v[2].vy == v[3].vy)
        t = 0x7FFFFFFF;
    else
        t = ((v[3].vx - v[2].vx) << 12) / (v[3].vy - v[2].vy);
    out[2] = t;

    if (v[3].vy == v[0].vy)
        t = 0x7FFFFFFF;
    else
        t = ((v[0].vx - v[3].vx) << 12) / (v[0].vy - v[3].vy);
    out[3] = t;
}
