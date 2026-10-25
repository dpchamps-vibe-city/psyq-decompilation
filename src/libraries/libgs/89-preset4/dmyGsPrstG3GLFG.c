#include "common.h"
#include <stdio.h>

extern s32 D_00002640;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstG3GLFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00002640 == 0) {
        printf(RO_STR_00001ED8 + 1440);
        D_00002640 = 1;
    }
    return arg3;
}
