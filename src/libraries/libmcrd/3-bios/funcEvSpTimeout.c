#include "common.h"
#include <libapi.h>

extern s32 B_00000748;

s32 funcEvSpTimeout(void) {
    B_00000748 = 1;
    return 0;
}
