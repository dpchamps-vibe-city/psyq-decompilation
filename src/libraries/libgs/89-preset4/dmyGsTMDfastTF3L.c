#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000025C0;
extern char RO_STR_00001ED8[];

s32 dmyGsTMDfastTF3L(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_000025C0 == 0) {
        printf(RO_STR_00001ED8 + 960);
        D_000025C0 = 1;
    }
    return arg3;
}
