#include "common.h"
#include <stdio.h>

extern s32 D_000025CC;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastTG3LFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000025CC == 0) {
        printf(RO_STR_00001ED8 + 1008);
        D_000025CC = 1;
    }
    return arg3;
}
