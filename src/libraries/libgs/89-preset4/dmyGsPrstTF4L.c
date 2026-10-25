#include "common.h"
#include <stdio.h>

extern s32 D_00002560;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstTF4L(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00002560 == 0) {
        printf(RO_STR_00001ED8 + 632);
        D_00002560 = 1;
    }
    return arg3;
}
