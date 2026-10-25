#include "common.h"
#include <stdio.h>

extern s32 D_0000257C;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstTG4LFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_0000257C == 0) {
        printf(RO_STR_00001ED8 + 724);
        D_0000257C = 1;
    }
    return arg3;
}
