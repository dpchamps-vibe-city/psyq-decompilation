#include "common.h"

extern u16 *StRingAddr;
extern s32 StRingIdx3;
extern s32 StRingSize;
extern s32 StEndFrame;

u16 StNextStatus(s32 *arg0, u16 **arg1) {
    volatile u16 *var_a2;

    var_a2 = (volatile u16 *) ((u8 *) StRingAddr + (StRingIdx3 << 5));
    if (*var_a2 == 1) {
        StRingIdx3 = 0;
        if (StEndFrame != 0) {
            *var_a2 = 0;
        }
        var_a2 = (volatile u16 *) ((u8 *) StRingAddr + (StRingIdx3 << 5));
    }
    *arg0 = (s32) ((u8 *) ((void *) ((u8 *) StRingAddr + (StRingSize << 5))) + (StRingIdx3 * 0x7E0));
    *arg1 = (u16 *) var_a2;
    return *var_a2;
}
