#include "common.h"

void StClearRing(void);
extern u16 *StRingAddr;
extern s32 StRingSize;

void StSetRing(u32 *arg0, u32 arg1) {
    StRingAddr = (u16 *)arg0;
    StRingSize = arg1;
    StClearRing();
}
