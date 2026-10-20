#include "common.h"

extern u8 D_00001273 __asm__("$LD_00001238+59");

u8 DS_lastread(void) {
    return D_00001273;
}
