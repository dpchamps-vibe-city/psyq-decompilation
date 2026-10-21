#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

s32 func_00000238();                   /* static */
extern s32 *D_00000274;

void GetDrawMode(DR_MODE *p) {
    s32 temp_s0;
    u32 temp_a1;
    u32 temp;

    temp_s0 = *D_00000274;
    temp_a1 = temp_s0 & 0x7FF;
    temp = ((u32) (temp_s0 & 0x8000) >> 4) | 0xE1000000;
    temp_a1 |= temp;
    p->code[0] = temp_a1;
    p->code[1] = func_00000238(2) | 0xE2000000;
}
