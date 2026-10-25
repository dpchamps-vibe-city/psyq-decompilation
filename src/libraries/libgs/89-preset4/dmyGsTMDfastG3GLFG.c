#include "common.h"
#include <stdio.h>

extern s32 D_00002628;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastG3GLFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00002628 == 0) {
        printf(RO_STR_00001ED8 + 1360);
        D_00002628 = 1;
    }
    return arg3;
}
