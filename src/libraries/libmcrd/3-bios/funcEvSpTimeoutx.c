#include "common.h"
#include <libapi.h>

extern s32 B_00000758;

s32 funcEvSpTimeoutx(void) {
    B_00000758 = 1;
    return 0;
}
