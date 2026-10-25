#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000CA8(VERTC *d, VERTC *a, VERTC *b);

static void func_00000CA8(VERTC *d, VERTC *a, VERTC *b)
{
    d->vx = (a->vx + b->vx) / 2;
    d->vy = (a->vy + b->vy) / 2;
    d->vz = (a->vz + b->vz) / 2;
    d->col.r = (a->col.r + b->col.r) >> 1;
    d->col.g = (a->col.g + b->col.g) >> 1;
    d->col.b = (a->col.b + b->col.b) >> 1;
    d->col.cd = a->col.cd;
    d->tu = (a->tu + b->tu) >> 1;
    d->tv = (a->tv + b->tv) >> 1;
}
