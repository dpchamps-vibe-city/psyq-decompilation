#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

void func_00000C38(VERT *arg0, VERT *arg1, VERT *arg2) {
    arg0->vx = (s16) ((s32) (arg1->vx + arg2->vx) / 2);
    arg0->vy = (s16) ((s32) (arg1->vy + arg2->vy) / 2);
    arg0->vz = (s16) ((s32) (arg1->vz + arg2->vz) / 2);
    arg0->tu = (u8) ((s32) (arg1->tu + arg2->tu) >> 1);
    arg0->tv = (u8) ((s32) (arg1->tv + arg2->tv) >> 1);
}
