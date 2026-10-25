#include "common.h"
#include <stdio.h>

extern s32 D_00002600;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastTF4L(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00002600 == 0) {
        printf(RO_STR_00001ED8 + 1200);
        D_00002600 = 1;
    }
    return arg3;
}
