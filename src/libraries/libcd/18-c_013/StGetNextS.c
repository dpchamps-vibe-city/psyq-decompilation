#include "common.h"

extern u16 *StRingAddr;
extern s32 StRingIdx3;
extern s32 StRingSize;

s32 StGetNextS(void **arg0, u16 **arg1) {
    u16 *var_a2;

    var_a2 = (u16 *) ((u8 *) StRingAddr + (StRingIdx3 << 5));
    if (*var_a2 == 1) {
        StRingIdx3 = 0;
        var_a2 = StRingAddr;
    }
    *var_a2 = 4;
    *arg0 = (void *) ((u8 *) ((void *) ((u8 *) StRingAddr + (StRingSize << 5))) + (StRingIdx3 * 0x7E0));
    *arg1 = var_a2;
    return 0;
}
