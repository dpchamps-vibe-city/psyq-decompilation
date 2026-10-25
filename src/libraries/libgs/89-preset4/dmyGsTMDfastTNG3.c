#include "common.h"
#include <stdio.h>

extern s32 D_000025D4;
extern char RO_STR_000022E8[];

s32 dmyGsTMDfastTNG3(s32 arg0, s32 arg1, s32 arg2) {
    if (D_000025D4 == 0) {
        printf(RO_STR_000022E8);
        D_000025D4 = 1;
    }
    return arg2;
}
