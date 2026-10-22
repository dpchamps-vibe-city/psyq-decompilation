#include "common.h"

long Krom2RawAdd(u32);                              /* extern */
s32 kanjitrans(s32);                                /* extern */

long Krom2RawAdd2(u32 code) {
    unsigned short s;
    s32 temp_v0;
    s32 var_s0;

    s = code;
    if ((u32) ((code + 0x7EC0) & 0xFFFF) < 0x37FU) {
        var_s0 = Krom2RawAdd(0x8140U);
        goto block_6;
    }
    if ((u32) ((code + 0x7AC0) & 0xFFFF) < 0x257U) {
        var_s0 = Krom2RawAdd(0x8140U) - 0x2000;
        goto block_6;
    }
    if ((u32) ((code + 0x7761) & 0xFFFF) < 0xFD4U) {
        var_s0 = Krom2RawAdd(0x889FU);
    } else {
        goto block_8;
    }
block_6:
    temp_v0 = kanjitrans(s);
    if (temp_v0 >= 0) {
        return var_s0 + (temp_v0 * 0x1E);
    }
    goto block_8;
block_8:
    return Krom2RawAdd(0x8140U);
}
