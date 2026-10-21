#include "common.h"

extern volatile u8 *D_00001B3C;
extern volatile u8 *D_00001B40;
extern volatile u8 *D_00001B48;
extern volatile u8 *D_00001B4C;

typedef struct {
    u8 pad0[0x180];
    u16 mvoll;
    u16 mvolr;
    u8 pad1[0x1AA - 0x184];
    u16 spucnt;
    u8 pad2[0x1B0 - 0x1AC];
    u16 cdvoll;
    u16 cdvolr;
    u8 pad3[0x1B8 - 0x1B4];
    u16 curmvoll;
    u16 curmvolr;
} SpuRegs;

extern SpuRegs *D_00001B50;

s32 CD_initvol(void) {
    u8 param[4];

    if (D_00001B50->curmvoll == 0) {
        if (D_00001B50->curmvolr == 0) {
            D_00001B50->mvoll = 0x3FFF;
            D_00001B50->mvolr = 0x3FFF;
        }
    }
    D_00001B50->cdvoll = 0x3FFF;
    D_00001B50->cdvolr = 0x3FFF;
    D_00001B50->spucnt = 0xC001;
    param[2] = 0x80;
    param[0] = 0x80;
    param[3] = 0;
    param[1] = 0;
    *D_00001B3C = 2;
    *D_00001B4C = param[0];
    *D_00001B40 = param[1];
    *D_00001B3C = 3;
    *D_00001B48 = param[2];
    *D_00001B4C = param[3];
    *D_00001B40 = 0x20;
    return 0;
}
