#include "common.h"
#include <sys/types.h>
#include <libgs.h>

static void func_00000B14(VERT *dst, VERT *a, VERT *b)
{
    dst->vx = (a->vx + b->vx) / 2;
    dst->vy = (a->vy + b->vy) / 2;
    dst->vz = (a->vz + b->vz) / 2;
}
