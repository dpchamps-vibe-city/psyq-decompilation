#include "common.h"

extern volatile u8 *D_00001B3C;
extern volatile u8 *D_00001B40;
extern volatile u8 *D_00001B4C;
extern volatile u8 D_00001B54[];
/* CD control register; local data label in the original member. */
extern s32 *D_00001B44 __asm__("$LD_00001B44");

void CD_flush(void) {
    *D_00001B3C = 1;
    if (*D_00001B40 & 7) {
        do {
            *D_00001B3C = 1;
            *D_00001B40 = 7;
            *D_00001B4C = 7;
        } while (*D_00001B40 & 7);
    }
    D_00001B54[2] = 0;
    D_00001B54[1] = D_00001B54[2];
    D_00001B54[0] = 2;
    *D_00001B3C = 0;
    *D_00001B40 = 0;
    *D_00001B44 = 0x1325;
}
