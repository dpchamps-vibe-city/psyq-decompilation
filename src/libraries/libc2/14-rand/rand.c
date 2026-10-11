#include "common.h"

extern u32 B_000000B0;

s32 rand(void) {
    u32 temp_v0;

    temp_v0 = (B_000000B0 * 0x41C64E6D) + 0x3039;
    B_000000B0 = temp_v0;
    return (temp_v0 >> 0x10) & 0x7FFF;
}
