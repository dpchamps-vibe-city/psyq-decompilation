#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000950(VERTC *d, VERTC *a, VERTC *b) {
    d->vx = (s16) ((s32) (a->vx + b->vx) / 2);
    d->vy = (s16) ((s32) (a->vy + b->vy) / 2);
    d->vz = (s16) ((s32) (a->vz + b->vz) / 2);
    d->col.r = (u8) ((s32) (a->col.r + b->col.r) >> 1);
    d->col.g = (u8) ((s32) (a->col.g + b->col.g) >> 1);
    d->col.b = (u8) ((s32) (a->col.b + b->col.b) >> 1);
    d->col.cd = a->col.cd;
}
