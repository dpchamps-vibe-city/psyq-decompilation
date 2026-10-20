#include "common.h"

extern volatile s32 LD_00001240 __asm__("$LD_00001240");

void DS_restart(void) {
    LD_00001240 = 1;
}
