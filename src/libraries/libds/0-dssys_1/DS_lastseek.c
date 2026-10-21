#include "common.h"

extern u8 D_00001272 __asm__("D_00001238+58");

u8 DS_lastseek(void) {
    return D_00001272;
}
