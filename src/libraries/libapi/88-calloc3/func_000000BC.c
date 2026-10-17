#include "common.h"

static void func_000000BC(u8 *arg0, s32 arg1) {
    u8 *temp_v1;
    u8 *var_a0;

    var_a0 = arg0;
    temp_v1 = var_a0 + arg1;
    if (var_a0 < temp_v1) {
        do {
            *var_a0 = 0;
            var_a0 += 1;
        } while (var_a0 < temp_v1);
    }
}
