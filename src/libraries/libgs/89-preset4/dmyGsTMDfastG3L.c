#include "common.h"
#include <stdio.h>

extern s32 D_000025B0;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastG3L(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000025B0 == 0) {
        printf(RO_STR_00001ED8 + 904);
        D_000025B0 = 1;
    }
    return arg3;
}
