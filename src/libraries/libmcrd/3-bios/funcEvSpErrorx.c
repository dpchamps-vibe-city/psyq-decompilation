#include "common.h"
#include <libapi.h>

extern s32 B_00000754;

s32 funcEvSpErrorx(void) {
    B_00000754 = 1;
    return 0;
}
