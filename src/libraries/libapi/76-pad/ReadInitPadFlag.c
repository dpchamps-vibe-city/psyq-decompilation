#include "common.h"

extern s32 D_00000300;

s32 ReadInitPadFlag(void) {
    return D_00000300;
}
