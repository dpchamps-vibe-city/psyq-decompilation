#include "common.h"

extern u8 D_0000126C __asm__("D_00001238+52");

u8 DS_lastcom(void) {
    return D_0000126C;
}
