#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static void func_00000CC4(VERTC *out, VERTC *in1, VERTC *in2) {
    out->vx = (s16) ((s32) (in1->vx + in2->vx) / 2);
    out->vy = (s16) ((s32) (in1->vy + in2->vy) / 2);
    out->vz = (s16) ((s32) (in1->vz + in2->vz) / 2);
    out->col.r = (u8) ((s32) (in1->col.r + in2->col.r) >> 1);
    out->col.g = (u8) ((s32) (in1->col.g + in2->col.g) >> 1);
    out->col.b = (u8) ((s32) (in1->col.b + in2->col.b) >> 1);
    out->col.cd = in1->col.cd;
    out->tu = (u8) ((s32) (in1->tu + in2->tu) >> 1);
    out->tv = (u8) ((s32) (in1->tv + in2->tv) >> 1);
}
