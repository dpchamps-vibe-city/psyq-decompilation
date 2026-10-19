#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern u_long StRingAddr;
extern s32 StRingSize;
extern s32 StRingIdx3;

u_long StFreeRing(u_long *base) {
    u_long p;
    s32 idx;
    s32 i;
    s16 n;

    idx = (base - (u_long *)(StRingAddr + (StRingSize << 5))) / 504;
    p = StRingAddr + (idx << 5);
    n = *(u_short *)(p + 6);
    if (*(short *)p == StLOCK) {
        for (i = 0; i < n; i++) {
            *(short *)(StRingAddr + ((i + idx) << 5)) = StFREE;
        }
        StRingIdx3 = i + idx;
        return 0;
    }
    return 1;
}
