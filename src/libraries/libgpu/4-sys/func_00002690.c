#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

void DMACallback(int, void *);

s32 func_00002430();                                /* static */
s32 func_00002A80(s32 arg0);                        /* static */
s32 func_00002908();                                /* static */
s32 func_0000293C();                                /* static */
extern s32 *D_0000331C;
extern s32 D_00003330;

static s32 func_00002690(s32 mode) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = SetIntrMask(0);
    _qout = 0;
    D_00003330 = temp_v0;
    _qin = _qout;
    temp_v1 = mode & 7;
    switch (temp_v1) {                              /* irregular */
    case 5:
    case 0:
        *D_0000330C = 0x401;
        *D_0000331C |= 0x800;
        *D_00003300 = 0;
        func_00002F60((u8 *) _que, 0, 0x1800);
        break;
    case 1:
    case 3:
        *D_0000330C = 0x401;
        *D_0000331C |= 0x800;
        *D_00003300 = 0x02000000;
        *D_00003300 = 0x01000000;
        break;
    }
    SetIntrMask(D_00003330);
    if (!(mode & 7)) {
        return func_00002A80(mode);
    }
    return 0;
}

#include "func_00002690_tail.inc"
