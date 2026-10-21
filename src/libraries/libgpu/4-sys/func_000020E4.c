#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern s32 *D_00003300;
extern s32 *D_00003304;
extern s32 *D_00003308;
extern s32 *D_0000330C;

static s32 *func_000020E4(s32 arg0);

static s32 *func_000020E4(s32 arg0) {
    s32 *p;
    if (0) {
        p = (s32 *) func_000020E4;
    }
    *D_00003300 = 0x04000002;
    *D_00003304 = arg0;
    *D_00003308 = 0;
    p = D_0000330C;
    *p = 0x01000401;
    return p;
}
