#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

int GetODE(void) {
    return (s32) ((*(u32 (**)()) ((u8 *) D_000031F0 + 0x38))() >> 0x1F);
}
