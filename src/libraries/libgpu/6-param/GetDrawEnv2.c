#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

static s32 func_00000238();            /* static */
extern s32 *D_00000274;

void GetDrawEnv2(DR_ENV *p) {
    s32 temp_s0;
    u32 temp_a1;
    u32 temp;

    temp_s0 = *D_00000274;
    (*(s8 *) ((u8 *) p + 3)) = 6;
    p->code[0] = func_00000238(3) | 0xE3000000;
    p->code[1] = func_00000238(4) | 0xE4000000;
    p->code[2] = func_00000238(5) | 0xE5000000;
    temp_a1 = temp_s0 & 0x7FF;
    temp = ((u32) (temp_s0 & 0x8000) >> 4) | 0xE1000000;
    temp_a1 |= temp;
    p->code[3] = temp_a1;
    p->code[4] = func_00000238(2, temp_a1) | 0xE2000000;
    p->code[5] = ((u32) (temp_s0 & 0x1800) >> 0xB) | 0xE6000000;
}
