#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000BF4(VERTC *dst, VERTC *a, VERTC *b) {
    dst->vx = (s16) ((s32) (a->vx + b->vx) / 2);
    dst->vy = (s16) ((s32) (a->vy + b->vy) / 2);
    dst->vz = (s16) ((s32) (a->vz + b->vz) / 2);
    dst->col.r = (u8) ((s32) (a->col.r + b->col.r) >> 1);
    dst->col.g = (u8) ((s32) (a->col.g + b->col.g) >> 1);
    dst->col.b = (u8) ((s32) (a->col.b + b->col.b) >> 1);
    dst->col.cd = a->col.cd;
}
