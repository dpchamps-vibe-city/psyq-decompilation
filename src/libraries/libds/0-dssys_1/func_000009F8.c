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

extern DsData D_00001238;

static s32 func_000009F8(s32 com, u8 *param) {
    u8 cmd;

    if ((com & 0xFF) == 2) {
        cmd = D_00001238.command;
        if (cmd == 0xE) {
            if ((D_00001238.lastmode ^ D_00001238.param[0]) & 0x80) {
                D_00001238.unkC = 0xF;
                D_00001238.unk8 = 2;
                D_00001238.unk28 = 3;
            } else {
                D_00001238.unk8 = 1;
                D_00001238.unkC = 0xB;
            }
            D_00001238.lastmode = D_00001238.param[0];
        } else if (cmd == 3) {
            D_00001238.unkC = 0x10;
            D_00001238.unk8 = 2;
            D_00001238.lastread = cmd;
            D_00001238.unk34 = 0x4B0;
        } else if (cmd == 6 || cmd == 0x1B) {
            D_00001238.unkC = 0x11;
            D_00001238.unk8 = 2;
            D_00001238.lastread = cmd;
            D_00001238.unk34 = 0x4B0;
        } else {
            switch (D_00001238.command) {
            case 2:
                *(DslLOC *)&D_00001238.lastpos = *(DslLOC *)&D_00001238.param[0];
                break;
            case 21:
            case 22:
                D_00001238.lastseek = D_00001238.command;
                break;
            case 3:
            case 6:
            case 27:
                D_00001238.lastread = D_00001238.command;
                break;
            }
            D_00001238.unk8 = 1;
            D_00001238.unkC = 0xB;
        }
    } else {
        if (D_00001238.status & 0x10) {
            D_00001238.unk8 = 2;
            D_00001238.unkC = 0xC;
        } else {
            D_00001238.unk8 = 1;
            D_00001238.unkC = 0xB;
        }
    }
    if (B_0000139C != 0 && LD_00001240 != 0) {
        B_0000139C(com & 0xFF, param);
    }
}
