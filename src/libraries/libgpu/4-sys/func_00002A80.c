#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern s32 *D_000032FC;
extern s32 *D_00003300;

static s32 func_00002A80(s32 arg0) {
    *D_00003300 = 0x10000007;
    if ((*D_000032FC & 0xFFFFFF) != 2) {
        *D_000032FC = (*D_00003300 & 0x3FFF) | 0xE1001000;
        *(volatile s32 *) D_000032FC;
        return 0;
    }
    if (!(arg0 & 8)) {
        return 1;
    }
    *D_00003300 = 0x09000001;
    return 2;
}
