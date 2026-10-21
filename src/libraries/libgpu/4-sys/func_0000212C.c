#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern s32 *D_000032FC;
extern s32 *D_00003300;

static s32 func_0000212C(s32 arg0);

static s32 func_0000212C(s32 arg0) {
    s32 *p;
    if (0) {
        p = (s32 *) func_0000212C;
    }
    *D_00003300 = arg0 | 0x10000000;
    return *D_000032FC & 0xFFFFFF;
}

#include "func_0000212C_tail.inc"
