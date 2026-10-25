#include "common.h"
#include <stdio.h>

extern s32 D_00002574;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDdivTNF4(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00002574 == 0) {
        printf(RO_STR_00001ED8 + 700);
        D_00002574 = 1;
    }
    return arg2;
}
