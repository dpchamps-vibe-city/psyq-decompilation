#include "common.h"

extern void CD_flush(void);

void DS_stop(void) {
    D_00001240.active = 0;
    CD_flush();
    D_00001240.unk48 = 0;
    D_00001240.timeout = 0;
    if ((D_00001240.system[0] == 2) && ((D_00001240.system[1] == 0xB) || (D_00001240.system[1] == 0x11) || (D_00001240.system[1] == 0x10))) {
        D_00001240.system[0] = 1;
        D_00001240.system[1] = 0xB;
    }
}
