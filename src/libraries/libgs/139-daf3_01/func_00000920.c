#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000920(VERT *d, VERT *a, VERT *b) {
    d->vx = (s16) ((s32) (a->vx + b->vx) / 2);
    d->vy = (s16) ((s32) (a->vy + b->vy) / 2);
    d->vz = (s16) ((s32) (a->vz + b->vz) / 2);
}
