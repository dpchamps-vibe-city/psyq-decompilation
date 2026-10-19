#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern u_long *StEmu_Addr;
extern void (*StFunc1)();
extern void (*StFunc2)();
extern s32 StRgb24;
extern s32 CChannel;
extern s32 StCHANNEL;
extern s32 Stframe_no;
extern s16 Stsector_offset;

void StSetStream(u_long mode, u_long start_frame, u_long end_frame, void (*func1)(), void (*func2)()) {
    StSetMask(1, start_frame, end_frame);
    StEmu_Addr = 0;
    StFunc1 = func1;
    StRgb24 = mode & 1;
    CChannel = 0;
    StCHANNEL = 0;
    Stsector_offset = 0;
    Stframe_no = 0;
    StFunc2 = func2;
}
