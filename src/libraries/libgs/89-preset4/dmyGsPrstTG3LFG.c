#include "common.h"
#include <stdio.h>

extern s32 D_000024FC;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstTG3LFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000024FC == 0) {
        printf(RO_STR_00001ED8 + 316);
        D_000024FC = 1;
    }
    return arg3;
}
