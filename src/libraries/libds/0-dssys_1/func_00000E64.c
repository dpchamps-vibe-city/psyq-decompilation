#include "common.h"

static void func_00000E64(s32 arg0, u8 *arg1) {
    if ((arg0 & 0xFF) == 2) {
        if (D_00001240.command == 0xE) {
            if ((D_00001240.lastmode ^ D_00001240.param[0]) & 0x80) {
                D_00001240.system[1] = 0xF;
                D_00001240.system[0] = arg0 & 0xFF;
                D_00001240.unk40 = 3;
            }
            D_00001240.lastmode = D_00001240.param[0];
        }
    }
    if ((arg0 & 0xFF) == 5) {
        if (D_00001240.status & 0x10) {
            D_00001240.system[0] = 2;
            D_00001240.system[1] = 0xC;
            if ((B_0000139C != 0) && (D_00001240.active != 0)) {
                B_0000139C(5, arg1);
            }
        } else {
            D_00001240.system[0] = 1;
            D_00001240.system[1] = 0xB;
        }
    }
}
