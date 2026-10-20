#include "common.h"

typedef struct {
    u8 pad0[0x0C];
    u8 command;
    u8 param[4];
    u8 pad1[0x0F];
    u8 status;
    u8 pad2[3];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 lastcom;
    u8 lastmode;
    DslLOC lastpos;
    u8 lastseek;
    u8 lastread;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    s32 unk20;
    s32 shell_open;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    u8 unk38;
    u8 unk39;
} DsData;

extern DsData DD __asm__("$LD_00001238");

s32 func_000009F8(s32 com, u8 *param) {
    u8 cmd;

    if ((com & 0xFF) == 2) {
        cmd = DD.command;
        if (cmd == 0xE) {
            if ((DD.lastmode ^ DD.param[0]) & 0x80) {
                DD.unkC = 0xF;
                DD.unk8 = 2;
                DD.unk28 = 3;
            } else {
                DD.unk8 = 1;
                DD.unkC = 0xB;
            }
            DD.lastmode = DD.param[0];
        } else if (cmd == 3) {
            DD.unkC = 0x10;
            DD.unk8 = 2;
            DD.lastread = cmd;
            DD.unk34 = 0x4B0;
        } else if (cmd == 6 || cmd == 0x1B) {
            DD.unkC = 0x11;
            DD.unk8 = 2;
            DD.lastread = cmd;
            DD.unk34 = 0x4B0;
        } else {
            switch (DD.command) {
            case 2:
                *(DslLOC *)&DD.lastpos = *(DslLOC *)&DD.param[0];
                break;
            case 21:
            case 22:
                DD.lastseek = DD.command;
                break;
            case 3:
            case 6:
            case 27:
                DD.lastread = DD.command;
                break;
            }
            DD.unk8 = 1;
            DD.unkC = 0xB;
        }
    } else {
        if (DD.status & 0x10) {
            DD.unk8 = 2;
            DD.unkC = 0xC;
        } else {
            DD.unk8 = 1;
            DD.unkC = 0xB;
        }
    }
    if (B_0000139C != 0 && LD_00001240 != 0) {
        B_0000139C(com & 0xFF, param);
    }
}
