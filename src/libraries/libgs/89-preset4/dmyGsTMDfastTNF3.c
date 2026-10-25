#include "common.h"
#include <stdio.h>

extern s32 D_000025C4;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastTNF3(s32 arg0, s32 arg1, s32 arg2) {
    if (D_000025C4 == 0) {
        printf(RO_STR_00001ED8 + 976);
        D_000025C4 = 1;
    }
    return arg2;
}
