#include "common.h"

s32 ResetRCnt(s32 arg0) {
    s32 temp_v1;

    temp_v1 = arg0 & 0xFFFF;
    if (temp_v1 >= 3) {
        return 0;
    }
    D_000001E4[temp_v1].count = 0;
    return 1;
}
