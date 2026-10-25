#include "common.h"
#include <stdio.h>

extern s32 D_00002634;
extern char RO_STR_00001ED8[];

s32 dmyGsPrstF3GLFG(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_00002634 == 0) {
        printf(RO_STR_00001ED8 + 1404);
        D_00002634 = 1;
    }
    return arg3;
}
