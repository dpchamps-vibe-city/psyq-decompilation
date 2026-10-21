#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

static u32 func_000016B8(s32 arg0, s32 arg1, s32 arg2) {
    return 0xE1000000 | (arg1 ? 0x200 : 0) | (arg0 ? 0x400 : 0) | (arg2 & 0x9FF);
}
