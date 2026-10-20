#include "common.h"

extern void CD_flush(void);

void DS_stop(void) {
    D_00001240.active = 0;
    CD_flush();
    (*(s32 *) ((u8 *) &D_00001240 + 0x48)) = 0;
    D_00001240.f44 = 0;
    if ((D_00001240.f20 == 2) && ((D_00001240.f24 == 0xB) || (D_00001240.f24 == 0x11) || (D_00001240.f24 == 0x10))) {
        D_00001260[0] = 1;
        D_00001260[1] = 0xB;
    }
}
