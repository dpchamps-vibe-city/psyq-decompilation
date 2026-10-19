#include "common.h"

extern u32 StRingAddr;

void init_ring_status(s32 arg0, u32 arg1) {
    s32 temp_v0;
    u32 var_a2;

    var_a2 = 0;
    if (arg1 != 0) {
        do {
            temp_v0 = var_a2 + arg0;
            var_a2 += 1;
            *(s32 *)(StRingAddr + (temp_v0 << 5)) = 0;
        } while (var_a2 < arg1);
    }
}
