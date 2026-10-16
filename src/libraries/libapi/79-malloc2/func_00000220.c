#include "common.h"

extern u32 *_max_heap;

void *func_00000220(u32 arg0) {
    u32 *p;

    if ((u32)(((s32)((s32)_max_heap - (s32)_AllocRestBlockTop) >> 2) * 4 - 8) < arg0) {
        return 0;
    }
    p = _AllocRestBlockTop - 1;
    _AllocRestBlockTop[-1] = arg0;
    _AllocRestBlockTop = (u32 *)((u8 *)_AllocRestBlockTop + (((arg0 >> 2) << 2) + 4));
    _AllocRestBlockTop[-1] = -2U;
    return p;
}
