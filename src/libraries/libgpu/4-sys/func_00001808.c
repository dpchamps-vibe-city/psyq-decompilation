#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

static u32 func_00001808(s32 arg0, s32 arg1) {
    return 0xE5000000 | ((arg1 & 0x7FF) << 0xB) | (arg0 & 0x7FF);
}
