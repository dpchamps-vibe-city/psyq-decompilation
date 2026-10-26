#include "common.h"

void setBetaCof(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s16 *arg4) {
    s32 t0;
    s32 t1;

    t0 = arg0 << 11;
    t1 = arg0 * 0x2AA;

    arg4[0] = ((arg1 << 11) - t1 - (arg2 << 11) + arg3 * 0x2AA) >> 12;
    arg4[1] = (t0 - (arg1 << 12) + (arg2 << 11)) >> 12;
    arg4[2] = ((arg2 << 11) - t0) >> 12;
    arg4[3] = (t1 + arg1 * 0xAAA + arg2 * 0x2AA) >> 12;
}
