#include "common.h"
#include <stdio.h>

extern s32 D_00002594;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDdivTNG4(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00002594 == 0) {
        printf(RO_STR_00001ED8 + 804);
        D_00002594 = 1;
    }
    return arg2;
}
