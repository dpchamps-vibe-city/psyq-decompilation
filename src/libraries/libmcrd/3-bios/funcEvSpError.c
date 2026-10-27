#include "common.h"
#include <libapi.h>

extern s32 B_00000744;

s32 funcEvSpError(void) {
    B_00000744 = 1;
    return 0;
}
