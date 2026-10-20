#include "common.h"

void func_00000E64(s32 arg0, u8 *arg1) {
    if ((arg0 & 0xFF) == 2) {
        if (DDx.command == 0xE) {
            if ((DDx.lastmode ^ DDx.param[0]) & 0x80) {
                DDx.unkC = 0xF;
                DDx.unk8 = arg0 & 0xFF;
                DDx.unk28 = 3;
            }
            DDx.lastmode = DDx.param[0];
        }
    }
    if ((arg0 & 0xFF) == 5) {
        if (DDx.status & 0x10) {
            DDx.unk8 = 2;
            DDx.unkC = 0xC;
            if ((B_0000139C != 0) && (DDx.active != 0)) {
                B_0000139C(5, arg1);
            }
        } else {
            DDx.unk8 = 1;
            DDx.unkC = 0xB;
        }
    }
}
