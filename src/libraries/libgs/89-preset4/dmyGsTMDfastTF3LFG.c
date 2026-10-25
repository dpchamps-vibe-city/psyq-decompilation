#include "common.h"
#include <stdio.h>

extern s32 D_000025BC;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastTF3LFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000025BC == 0) {
        printf(RO_STR_00001ED8 + 944);
        D_000025BC = 1;
    }
    return arg3;
}
