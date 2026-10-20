#include "common.h"

extern u8 D_0000126D __asm__("$LD_00001238+53");

u8 DS_lastmode(void) {
    return D_0000126D;
}
