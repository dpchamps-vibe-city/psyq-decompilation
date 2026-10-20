#include "common.h"

extern volatile u8 *D_00001B3C;
extern volatile u8 *D_00001B40;
extern volatile u8 *D_00001B48;
extern volatile u8 *D_00001B4C;

s32 CD_vol(u8 *arg0) {
    *D_00001B3C = 2;
    *D_00001B4C = arg0[0];
    *D_00001B40 = arg0[1];
    *D_00001B3C = 3;
    *D_00001B48 = arg0[2];
    *D_00001B4C = arg0[3];
    *D_00001B40 = 0x20;
    return 0;
}
