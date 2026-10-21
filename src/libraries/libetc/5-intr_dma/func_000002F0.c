#include "common.h"

static void func_000002F0(DMAFunc *arg0, s32 arg1) {
    u32 i;

    i = arg1 - 1;
    if (arg1 != 0) {
        do {
            *arg0 = 0;
            i -= 1;
            arg0 += 1;
        } while (i != (u32)-1);
    }
}
