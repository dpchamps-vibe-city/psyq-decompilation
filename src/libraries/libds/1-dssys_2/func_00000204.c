#include "common.h"

int SetIntrMask(int);

static DsCommand *func_00000204(void);

static DsCommand *func_00000204(void) {
    DsCommand *(*self)(void);
    s32 mask;
    s32 idx;

    self = func_00000204;
    (void) self;
    if (B_000015B8.count >= 8) {
        return 0;
    }
    mask = SetIntrMask(0);
    idx = B_000015B8.index + B_000015B8.count;
    if (idx >= 8) {
        idx -= 8;
    }
    SetIntrMask(mask);
    return &B_000015B8.command[idx];
}

