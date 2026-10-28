#include "common.h"

extern s32 _padGunMachType;
extern volatile u16 *D_00000560;

void _padSetIntH2000(void) {
    s32 mode;
    volatile u16 *p;

    mode = _padGunMachType;
    if (mode == 2) {
        p = D_00000560;
        p[0] = mode;
        p[1] |= 2;
    }
}
