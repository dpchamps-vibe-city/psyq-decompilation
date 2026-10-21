#include "common.h"


static s32 func_000009F8(s32 com, u8 *param) {
    u8 cmd;

    if ((com & 0xFF) == 2) {
        cmd = D_00001240.command;
        if (cmd == 0xE) {
            if ((D_00001240.lastmode ^ D_00001240.param[0]) & 0x80) {
                D_00001240.system[1] = 0xF;
                D_00001240.system[0] = 2;
                D_00001240.unk40 = 3;
            } else {
                D_00001240.system[0] = 1;
                D_00001240.system[1] = 0xB;
            }
            D_00001240.lastmode = D_00001240.param[0];
        } else if (cmd == 3) {
            D_00001240.system[1] = 0x10;
            D_00001240.system[0] = 2;
            D_00001240.lastread = cmd;
            D_00001240.unk4C = 0x4B0;
        } else if (cmd == 6 || cmd == 0x1B) {
            D_00001240.system[1] = 0x11;
            D_00001240.system[0] = 2;
            D_00001240.lastread = cmd;
            D_00001240.unk4C = 0x4B0;
        } else {
            switch (D_00001240.command) {
            case 2:
                *(DslLOC *)&D_00001240.lastpos = *(DslLOC *)&D_00001240.param[0];
                break;
            case 21:
            case 22:
                D_00001240.lastseek = D_00001240.command;
                break;
            case 3:
            case 6:
            case 27:
                D_00001240.lastread = D_00001240.command;
                break;
            }
            D_00001240.system[0] = 1;
            D_00001240.system[1] = 0xB;
        }
    } else {
        if (D_00001240.status & 0x10) {
            D_00001240.system[0] = 2;
            D_00001240.system[1] = 0xC;
        } else {
            D_00001240.system[0] = 1;
            D_00001240.system[1] = 0xB;
        }
    }
    if (B_0000139C != 0 && D_00001240.active != 0) {
        B_0000139C(com & 0xFF, param);
    }
}
