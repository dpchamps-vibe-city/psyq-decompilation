#include "common.h"

int SetIntrMask(int);

#define func_00000204 $Lfunc_00000204

static DsCqCommand *func_00000204(void);

static DsCqCommand *func_00000204(void) {
    DsCqCommand *(*self)(void);
    s32 mask;
    s32 idx;

    self = func_00000204;
    (void) self;
    if ($LB_000015B8.count >= 8) {
        return 0;
    }
    mask = SetIntrMask(0);
    idx = $LB_000015B8.index + $LB_000015B8.count;
    if (idx >= 8) {
        idx -= 8;
    }
    SetIntrMask(mask);
    return &$LB_000015B8.command[idx];
}

#undef func_00000204

#define PUBLISHED_ENTRY() static DsCqCommand *func_00000204(void) { return $Lfunc_00000204(); }
PUBLISHED_ENTRY();
