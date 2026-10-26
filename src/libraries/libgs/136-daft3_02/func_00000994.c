#include "common.h"
#include <sys/types.h>
#include <libgs.h>

static void func_00000994(VERT *d, VERT *a, VERT *b)
{
    d->vx = (a->vx + b->vx) / 2;
    d->vy = (a->vy + b->vy) / 2;
    d->vz = (a->vz + b->vz) / 2;
    d->tu = (a->tu + b->tu) / 2;
    d->tv = (a->tv + b->tv) / 2;
}
