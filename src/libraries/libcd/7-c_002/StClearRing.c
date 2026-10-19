#include "common.h"

void init_ring_status(s32, s32);                    /* extern */
extern s32 StCdIntrFlag;
extern s32 StFinalSector;
extern s32 StRingIdx1;
extern s32 StRingIdx2;
extern s32 StRingIdx3;
extern s32 StRingSize;
extern s32 Stframe_no;
extern s16 Stsector_offset;

void StClearRing(void) {
    StRingIdx3 = 0;
    StRingIdx2 = 0;
    StRingIdx1 = 0;
    StFinalSector = 0;
    init_ring_status(0, StRingSize);
    StCdIntrFlag = 0;
    Stsector_offset = 0;
    Stframe_no = 0;
}
