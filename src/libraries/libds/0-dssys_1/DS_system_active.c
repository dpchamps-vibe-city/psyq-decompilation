#include "common.h"

extern s32 D_00001238_8 __asm__("$LD_00001238+8");

s32 DS_system_active(void) {
    return D_00001238_8;
}
