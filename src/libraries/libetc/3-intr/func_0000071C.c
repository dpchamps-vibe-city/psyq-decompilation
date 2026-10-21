#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

static void func_0000071C(s32 *arg0, s32 arg1) {
    s32 *var_a0;
    s32 var_v0;

    var_a0 = arg0;
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_a0 = 0;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}
