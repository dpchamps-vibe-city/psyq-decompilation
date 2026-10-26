#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000BF4(VERTC *dst, VERTC *a, VERTC *b) {
    dst->vx = (a->vx + b->vx) / 2;
    dst->vy = (a->vy + b->vy) / 2;
    dst->vz = (a->vz + b->vz) / 2;
    dst->col.r = (a->col.r + b->col.r) / 2;
    dst->col.g = (a->col.g + b->col.g) / 2;
    dst->col.b = (a->col.b + b->col.b) / 2;
    dst->col.cd = a->col.cd;
}
