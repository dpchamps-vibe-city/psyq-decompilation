#include "common.h"

extern u8 D_0000126E __asm__("$LD_00001238+54");

u8 *DS_lastpos(void) {
    return &D_0000126E;
}
