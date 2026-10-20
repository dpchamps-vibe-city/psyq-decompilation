#include "common.h"

extern u8 D_00001258 __asm__("$LD_00001238+32");

u8 DS_status(void) {
    return D_00001258;
}
