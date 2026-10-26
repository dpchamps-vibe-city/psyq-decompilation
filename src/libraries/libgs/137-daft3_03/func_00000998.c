#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000998(VERT *d, VERT *a, VERT *b) {
    d->vx = (s16) ((s32) (a->vx + b->vx) / 2);
    d->vy = (s16) ((s32) (a->vy + b->vy) / 2);
    d->vz = (s16) ((s32) (a->vz + b->vz) / 2);
    d->tu = (u8) ((s32) (a->tu + b->tu) >> 1);
    d->tv = (u8) ((s32) (a->tv + b->tv) >> 1);
}
