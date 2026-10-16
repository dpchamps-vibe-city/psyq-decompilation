#include "common.h"

extern vu16 *D_00000304;

static s32 func_00000254(void) {
    volatile s32 i[4];

    D_00000304[5] = 0;
    i[0] = 10;
    while (--i[0] != -1) {
    }
    return 0;
}
