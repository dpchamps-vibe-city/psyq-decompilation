#include "common.h"
#include <libapi.h>

extern s32 B_00000750;

s32 funcEvSpIOEx(void) {
    B_00000750 = 1;
    return 0;
}
