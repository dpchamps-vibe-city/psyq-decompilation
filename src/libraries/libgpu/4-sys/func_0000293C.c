#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern s32 *D_00003300;
extern s32 *D_00003304;
extern s32 *D_0000330C;
extern s32 *D_0000331C;
extern s32 D_00003330;
extern s32 D_00003334;
extern s32 D_00003338;
extern char RO_STR_00003168[];

static s32 func_0000293C(void) {
    s32 temp_v0;

    if ((D_00003334 < VSync(-1)) || (D_00003338++ > 0xF0000)) {
        /* The original reads the GPU status once before the report and once
           as printf's stat argument; both are volatile reads. */
        *(volatile s32 *) D_00003300;
        printf(RO_STR_00003168, (_qin - _qout) & 0x3F, *D_00003300, *D_0000330C, *D_00003304);
        temp_v0 = SetIntrMask(0);
        _qout = 0;
        D_00003330 = temp_v0;
        _qin = _qout;
        *D_0000330C = 0x401;
        *D_0000331C |= 0x800;
        *D_00003300 = 0x02000000;
        *D_00003300 = 0x01000000;
        SetIntrMask(D_00003330);
        return -1;
    }
    return 0;
}
