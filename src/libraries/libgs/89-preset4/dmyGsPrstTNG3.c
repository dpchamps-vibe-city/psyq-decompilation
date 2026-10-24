#include "common.h"
#include <stdio.h>

extern s32 D_00002504;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstTNG3(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00002504 == 0) {
        printf(RO_STR_00001ED8 + 340);
        D_00002504 = 1;
    }
    return arg3;
}
