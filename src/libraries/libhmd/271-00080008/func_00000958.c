#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static void func_00000958(SVECTOR *dst, SVECTOR *a, SVECTOR *b) {
    dst->vx = (a->vx + b->vx) / 2;
    dst->vy = (a->vy + b->vy) / 2;
    dst->vz = (a->vz + b->vz) / 2;
}
