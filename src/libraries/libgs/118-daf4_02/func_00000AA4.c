#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000AA4(VERT *dst, VERT *a, VERT *b) {
    dst->vx = (a->vx + b->vx) / 2;
    dst->vy = (a->vy + b->vy) / 2;
    dst->vz = (a->vz + b->vz) / 2;
}
