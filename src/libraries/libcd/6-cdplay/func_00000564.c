#include "common.h"

void func_00000564(void) {
    u_char result[8];

    D_00000800 = 0;
    CdReadyCallback(0);
    CdControl(1, 0, 0);
    while (CdControlB(9, 0, result) == 0) {
        if (result[0] & 0x10) {
            break;
        }
    }
    D_000007FC = -1;
}
