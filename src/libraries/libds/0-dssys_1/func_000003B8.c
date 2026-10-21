#include "common.h"


extern void CD_flush(void);
extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);
extern void parcpy(u8 *dst, u8 *src);

static s32 func_000003B8(u8 com, u8 *param) {
    s32 t;

    CD_flush();
    D_00001240.command = com;
    if (param != 0) {
        parcpy(D_00001240.param, param);
        D_00001240.param_ptr = D_00001240.param;
    } else {
        D_00001240.param_ptr = 0;
    }
    D_00001240.timeout = (t = D_00001294[D_00001240.command]) ? t * 0x3C : 0x1E;
    D_00001240.unk48 = 0;
    switch (D_00001240.command) {
    case 9:
        if (D_00001240.unk50 != 0 && D_00001240.unk51 == D_00001240.command) {
            D_00001240.command = 1;
        }
        break;
    case 7:
        if (D_00001240.flags[3] == 1) {
            D_00001240.command = D_00001240.flags[3];
        }
        break;
    case 8:
        if (D_00001240.flags[3] != 1) {
            D_00001240.command = 1;
        }
        break;
    }
    if (D_00001240.command == 1) {
        D_00001240.param_ptr = 0;
        D_00001240.timeout = (t = D_00001294[D_00001240.command]) ? t * 0x3C : 0x1E;
    }
    if (CD_cw(D_00001240.command, D_00001240.param_ptr, 0, 1) != 0) {
        D_00001240.unk48 = 0;
        D_00001240.timeout = 0;
        return 0;
    }
    D_00001240.lastcom = D_00001240.command;
    if (D_00001240.command != 1) {
        D_00001240.unk51 = D_00001240.command;
        D_00001240.unk50 = 0;
    }
    return 1;
}
