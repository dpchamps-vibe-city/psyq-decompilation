#include "common.h"

static void func_000000C8(void) {
    s32 var_s1;
    VBlankFunc *var_s0;
    VBlankFunc temp_v0;

    var_s1 = 0;
    var_s0 = D_00000190;
    Vcount += 1;
    do {
        temp_v0 = *var_s0;
        if (temp_v0 != 0) {
            temp_v0();
        }
        var_s1 += 1;
        var_s0 += 1;
    } while (var_s1 < 8);
}
