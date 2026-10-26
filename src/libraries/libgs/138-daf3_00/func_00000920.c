#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000920(VERT *d, VERT *a, VERT *b)
{
    d->vx = (a->vx + b->vx) / 2;
    d->vy = (a->vy + b->vy) / 2;
    d->vz = (a->vz + b->vz) / 2;
}
