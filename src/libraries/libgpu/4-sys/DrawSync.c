#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_00003064[];

int DrawSync(int mode) {
    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_00003064, mode);
    }
    return (*(s32 (**)(s32)) ((u8 *) D_000031F0 + 0x3C))(mode);
}
