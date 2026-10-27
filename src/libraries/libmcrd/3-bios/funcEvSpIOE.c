#include "common.h"
#include <libapi.h>

extern s32 B_00000740;

s32 funcEvSpIOE(void) {
    B_00000740 = 1;
    return 0;
}
