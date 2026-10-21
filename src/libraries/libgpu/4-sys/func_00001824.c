#include "common.h"
#include "include_asm.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

static u32 func_00001824(RECT *arg0) {
    u_long code[4];

    if (arg0) {
        code[0] = (arg0->x & 0xFF) >> 3;
        code[2] = (-arg0->w & 0xFF) >> 3;
        code[1] = (arg0->y & 0xFF) >> 3;
        code[3] = (-arg0->h & 0xFF) >> 3;
        return 0xE2000000 | (code[1] << 15) | (code[0] << 10) | (code[3] << 5) | code[2];
    }
    return 0;
}

#include "func_00001824_tail.inc"
