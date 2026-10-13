#include "common.h"

s32 StopRCnt(u32 counter) {
    D_000001E0[1] &= ~D_000001E8[counter & 0xFFFF];
    return 1;
}
