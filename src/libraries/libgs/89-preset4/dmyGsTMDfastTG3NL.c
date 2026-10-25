#include "common.h"
#include <stdio.h>

extern s32 D_000025C8;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastTG3NL(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000025C8 == 0) {
        printf(RO_STR_00001ED8 + 992);
        D_000025C8 = 1;
    }
    return arg3;
}
