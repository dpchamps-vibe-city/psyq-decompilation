#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

static u32 func_00001770(s16 arg0, s16 arg1) {
    s16 var_v0;
    s16 var_a1;
    s32 var_v1;

    var_v0 = arg0;
    var_v0 = var_v0 < 0 ? 0 : (var_v0 > *(s16 *) ((u8 *) &GEnv + 4) - 1 ? *(s16 *) ((u8 *) &GEnv + 4) - 1 : var_v0);
    if (arg1 >= 0) {
        var_v1 = arg1 & 0x3FF;
        if (arg1 > *(s16 *) ((u8 *) &GEnv + 6) - 1) {
            arg1 = *(s16 *) ((u8 *) &GEnv + 6) - 1;
            goto block_8;
        }
        goto block_9;
    } else {
        arg1 = 0;
    }
block_8:
    var_v1 = arg1 & 0x3FF;
block_9:
    return 0xE4000000 | (var_v1 << 0xA) | (var_v0 & 0x3FF);
}
