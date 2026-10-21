#include "common.h"


static void func_00000BDC(s32 arg0, u8 *arg1) {
    if (D_00001240.system[1] == 0xC) {
        D_00001240.system[1] = 0xD;
    }
    if ((arg0 & 0xFF) == 2) {
        if (D_00001240.system[1] == 0xD) {
            if (!(D_00001240.status & 0x10)) {
                D_00001240.system[1] = 0xE;
                D_00001240.system[0] = 2;
                D_00001240.system[2] = 0x15;
                D_00001240.shell_open = D_00001240.shell_open + 1;
            }
        } else if (D_00001240.system[1] == 0xE) {
            if (D_00001240.system[2] == 0x15) {
                if (!(D_00001240.status & 0x10)) {
                    D_00001240.system[0] = 2;
                    D_00001240.system[1] = D_00001240.system[1];
                    D_00001240.system[2] = 0x16;
                    D_00001240.unk38 = 0;
                }
            } else if (D_00001240.system[2] == 0x16) {
                if (D_00001240.status & 2) {
                    D_00001240.system[0] = 2;
                    D_00001240.system[1] = D_00001240.system[1];
                    D_00001240.system[2] = 0x17;
                } else if (D_00001240.unk38 >= 0x12D) {
                    D_00001240.system[0] = 3;
                    if (B_000013A4 != 0) {
                        B_000013A4(5, arg1);
                    }
                }
            } else if (D_00001240.system[2] == 0x17) {
                D_00001240.system[0] = 2;
                D_00001240.system[1] = D_00001240.system[1];
                D_00001240.system[2] = 0x18;
            } else if (D_00001240.system[2] == 0x18) {
                if (D_00001240.status == 2) {
                    D_00001240.system[0] = 1;
                    D_00001240.system[1] = 0xB;
                    D_00001240.system[2] = 0;
                    if (B_000013A4 != 0) {
                        B_000013A4(2, arg1);
                    }
                }
            }
        } else if (((u32)(D_00001240.system[1] - 0x10) < 2) && (D_00001240.unk4C == 0) &&
                   !(D_00001240.status & 2)) {
            D_00001240.system[0] = 1;
            D_00001240.system[1] = 0xB;
            if ((B_000013A0 != 0) && (D_00001240.active != 0)) {
                B_000013A0(5, arg1);
            }
            if ((B_0000139C != 0) && (D_00001240.active != 0)) {
                B_0000139C(5, arg1);
            }
        }
    } else {
        if (D_00001240.status & 0x10) {
            D_00001240.system[0] = 2;
            D_00001240.system[1] = 0xC;
            return;
        }
        if ((u32)(D_00001240.system[1] - 0x10) < 2) {
            D_00001240.system[0] = 1;
            D_00001240.system[1] = 0xB;
        }
    }
}
