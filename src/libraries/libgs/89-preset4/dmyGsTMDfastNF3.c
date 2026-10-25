#include "common.h"
#include <stdio.h>

extern s32 D_000025A4;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastNF3(s32 arg0, s32 arg1, s32 arg2) {
    if (D_000025A4 == 0) {
        printf(RO_STR_00001ED8 + 860);
        D_000025A4 = 1;
    }
    return arg2;
}
