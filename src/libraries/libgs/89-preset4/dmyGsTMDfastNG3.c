#include "common.h"
#include <stdio.h>

extern s32 D_000025B4;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastNG3(s32 arg0, s32 arg1, s32 arg2) {
    if (D_000025B4 == 0) {
        printf(RO_STR_00001ED8 + 916);
        D_000025B4 = 1;
    }
    return arg2;
}
