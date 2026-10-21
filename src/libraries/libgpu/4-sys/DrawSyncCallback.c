#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern char RO_STR_00003034[];

u_long DrawSyncCallback(void (*func)(void)) {
    u32 temp_v0;

    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_00003034, func);
    }
    temp_v0 = *(u32 *) ((u8 *) &(&GEnv)[2] + 0xA);
    (*(void (**)()) ((u8 *) &(&GEnv)[2] + 0xA)) = func;
    return temp_v0;
}
