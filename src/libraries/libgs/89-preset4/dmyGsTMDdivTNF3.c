#include "common.h"
#include <stdio.h>

extern s32 D_000024F4;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDdivTNF3(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000024F4 == 0) {
        printf(RO_STR_00001ED8 + 292);
        D_000024F4 = 1;
    }
    return arg3;
}
