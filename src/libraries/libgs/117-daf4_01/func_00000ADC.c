#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000ADC(VERT *dst, VERT *a, VERT *b) {
    dst->vx = (s16) ((s32) (a->vx + b->vx) / 2);
    dst->vy = (s16) ((s32) (a->vy + b->vy) / 2);
    dst->vz = (s16) ((s32) (a->vz + b->vz) / 2);
}
