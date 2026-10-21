#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern s32 D_00003334;
extern s32 D_00003338;

static s32 func_00002908(void) {
    D_00003334 = VSync(-1) + 0xF0;
    D_00003338 = 0;
}
