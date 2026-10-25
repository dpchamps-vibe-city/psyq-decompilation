#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000A1C(VERT *a, VERT *b, VERT *c, GsADIV_FT4 *s);
int func_00000B34(POLY_FT4 *p, GsADIV_FT4 *s);

static void func_00000CF0(VERT *d, VERT *a, VERT *b)
{
    d->vx = (a->vx + b->vx) / 2;
    d->vy = (a->vy + b->vy) / 2;
    d->vz = (a->vz + b->vz) / 2;
    d->tu = (a->tu + b->tu) / 2;
    d->tv = (a->tv + b->tv) / 2;
}
