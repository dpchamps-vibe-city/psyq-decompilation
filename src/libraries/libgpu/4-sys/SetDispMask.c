#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_00003050[];

void SetDispMask(int mask) {
    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_00003050, mask);
    }
    if (mask == 0) {
        func_00002F60(&(*(u8 *) ((u8 *) &(&GEnv)[2] + 0x6A)), -1, 0x14);
    }
    ((void (*)(u32)) D_000031F0->unk10)(mask ? 0x03000000 : 0x03000001);
}
