#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern char RO_STR_00002FF4[];

int SetGraphDebug(int level) {
    u8 temp_s0;

    temp_s0 = *(u8 *) ((u8 *) &GEnv + 2);
    (*(u8 *) ((u8 *) &GEnv + 2)) = (u8) level;
    if (level & 0xFF) {
        GPU_printf(RO_STR_00002FF4, *(u8 *) ((u8 *) &GEnv + 2), *(u8 *) ((u8 *) &(&GEnv)[2] + -2), *(u8 *) ((u8 *) &(&GEnv)[2] + 1));
    }
    return (s32) temp_s0;
}
