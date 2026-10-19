#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern u_long *StEmu_Addr;
extern s32 StEmu_Idx;
extern void (*StFunc1)();
extern void (*StFunc2)();
extern s32 StRgb24;

void StSetEmulate(u_long *addr, u_long mode, u_long start_frame, u_long end_frame, void (*func1)(), void (*func2)()) {
    StSetMask(1, start_frame, end_frame);
    StEmu_Addr = addr;
    StEmu_Idx = 0;
    StRgb24 = 0;
    StFunc1 = func1;
    StFunc2 = func2;
}
