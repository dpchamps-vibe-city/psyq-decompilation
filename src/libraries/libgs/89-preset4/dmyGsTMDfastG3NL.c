#include "common.h"
#include <stdio.h>

extern s32 D_000025A8;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastG3NL(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000025A8 == 0) {
        printf(RO_STR_00001ED8 + 872);
        D_000025A8 = 1;
    }
    return arg3;
}
