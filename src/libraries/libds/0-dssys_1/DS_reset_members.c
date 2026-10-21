#include "common.h"

typedef unsigned char u_char;

DslLOC *DsIntToPos(int i, DslLOC *p);



void DS_reset_members(void) {
    s32 i;

    u8 *p;
    u8 *q;

    D_00001240.active = 0;
    D_00001240.command = 0;
    i = 3;
    p = &D_00001240.param[3];
    for (; i >= 0; i--) {
        *p-- = 0;
    }
    D_00001240.param_ptr = 0;
    i = 7;
    q = &D_00001240.result[7];
    for (; i >= 0; i--) {
        *q-- = 0;
    }
    D_00001240.status = 0;
    D_00001240.unk1C = 0;
    D_00001240.system[0] = 2;
    D_00001240.system[1] = 0xE;
    D_00001240.system[2] = 0x15;
    D_00001240.lastcom = 0;
    D_00001240.lastmode = 0;
    DsIntToPos(0, &D_00001240.lastpos);
    D_00001240.lastseek = 0;
    D_00001240.lastread = 0;
    D_00001240.flags[0] = 0;
    D_00001240.flags[1] = 0;
    D_00001240.flags[2] = 0;
    D_00001240.flags[3] = 0;
    D_00001240.unk38 = 0;
    D_00001240.shell_open = 1;
    D_00001240.unk40 = 0;
    D_00001240.unk48 = 0;
    D_00001240.timeout = 0;
    D_00001240.unk4C = 0;
    D_00001240.unk50 = 0;
    D_00001240.unk51 = 0;
}
