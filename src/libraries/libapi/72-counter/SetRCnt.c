#include "common.h"

s32 SetRCnt(s32 arg0, u16 arg1, s32 arg2) {
    s32 temp_t0;
    u16 var_a3;

    temp_t0 = arg0 & 0xFFFF;
    var_a3 = 0x48;
    if (temp_t0 >= 3) {
        return 0;
    }
    D_000001E4[temp_t0].mode = 0;
    D_000001E4[temp_t0].target = arg1;
    if ((u32) temp_t0 < 2U) {
        if (arg2 & 0x10) {
            var_a3 = 0x49;
        }
        if (!(arg2 & 1)) {
            var_a3 |= 0x100;
        }
    } else {
        if (temp_t0 == 2) {
            if (!(arg2 & 1)) {
                var_a3 = 0x248;
            }
        }
    }
    if (arg2 & 0x1000) {
        var_a3 |= 0x10;
    }
    D_000001E4[temp_t0].mode = var_a3;
    return 1;
}
