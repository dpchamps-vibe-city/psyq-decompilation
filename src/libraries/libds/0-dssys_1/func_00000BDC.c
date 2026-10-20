#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 active;
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
    u8 lastpos[4];
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
} DsDataB;

extern DsDataB DDx __asm__("$LD_00001238");
extern volatile DslCB B_000013A4 __asm__("$LB_000013A4");

void func_00000BDC(s32 arg0, u8 *arg1) {
    if (DDx.unkC == 0xC) {
        DDx.unkC = 0xD;
    }
    if ((arg0 & 0xFF) == 2) {
        if (DDx.unkC == 0xD) {
            if (!(DDx.status & 0x10)) {
                DDx.unkC = 0xE;
                DDx.unk8 = 2;
                DDx.unk10 = 0x15;
                DDx.shell_open = DDx.shell_open + 1;
            }
        } else if (DDx.unkC == 0xE) {
            if (DDx.unk10 == 0x15) {
                if (!(DDx.status & 0x10)) {
                    DDx.unk8 = 2;
                    DDx.unkC = DDx.unkC;
                    DDx.unk10 = 0x16;
                    DDx.unk20 = 0;
                }
            } else if (DDx.unk10 == 0x16) {
                if (DDx.status & 2) {
                    DDx.unk8 = 2;
                    DDx.unkC = DDx.unkC;
                    DDx.unk10 = 0x17;
                } else if (DDx.unk20 >= 0x12D) {
                    DDx.unk8 = 3;
                    if (B_000013A4 != 0) {
                        B_000013A4(5, arg1);
                    }
                }
            } else if (DDx.unk10 == 0x17) {
                DDx.unk8 = 2;
                DDx.unkC = DDx.unkC;
                DDx.unk10 = 0x18;
            } else if (DDx.unk10 == 0x18) {
                if (DDx.status == 2) {
                    DDx.unk8 = 1;
                    DDx.unkC = 0xB;
                    DDx.unk10 = 0;
                    if (B_000013A4 != 0) {
                        B_000013A4(2, arg1);
                    }
                }
            }
        } else if (((u32)(DDx.unkC - 0x10) < 2) && (DDx.unk34 == 0) &&
                   !(DDx.status & 2)) {
            DDx.unk8 = 1;
            DDx.unkC = 0xB;
            if ((B_000013A0 != 0) && (DDx.active != 0)) {
                B_000013A0(5, arg1);
            }
            if ((B_0000139C != 0) && (DDx.active != 0)) {
                B_0000139C(5, arg1);
            }
        }
    } else {
        if (DDx.status & 0x10) {
            DDx.unk8 = 2;
            DDx.unkC = 0xC;
            return;
        }
        if ((u32)(DDx.unkC - 0x10) < 2) {
            DDx.unk8 = 1;
            DDx.unkC = 0xB;
        }
    }
}
