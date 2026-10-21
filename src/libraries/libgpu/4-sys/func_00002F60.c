#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

static void func_00002F60(u8 *arg0, int arg1, int arg2) {
    s32 var_v0;
    u8 *var_a0;

    var_a0 = arg0;
    var_v0 = arg2 - 1;
    if (arg2 != 0) {
        do {
            *var_a0 = arg1;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}
