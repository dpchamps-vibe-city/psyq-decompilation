#include "common.h"

extern s32 *_AllocRestBlockTop;
extern s32 _Candidate;
extern s32 *_TopAllocArea;
extern s32 *_max_heap;

void InitHeap2(s32 *arg0, u32 arg1) {
    _AllocRestBlockTop = arg0;
    _TopAllocArea = arg0;
    *arg0 = -2;
    _max_heap = &arg0[arg1 >> 2] + 1;
    _Candidate = 0;
    _AllocRestBlockTop += 1;
}
