#include "common.h"

extern u16 *StRingAddr;
extern u16 StRingIdx1;
extern u16 StRingIdx3;
extern s32 StRingSize;

void StRingStatus(short *free_sectors, short *over_sectors) {
    s32 i;
    u16 *p;

    i = StRingSize;
    *free_sectors = 0;
    *over_sectors = StRingIdx1 - StRingIdx3;
    if (*over_sectors < 0) {
        while (--i >= 0) {
            p = (u16 *)((u8 *)StRingAddr + (i << 5));
            if (*p == 1) {
                break;
            }
        }
        *over_sectors += ++i;
    }
    while (--i >= 0) {
        p = (u16 *)((u8 *)StRingAddr + (i << 5));
        if (*p == 0) {
            (*free_sectors)++;
        }
    }
}
