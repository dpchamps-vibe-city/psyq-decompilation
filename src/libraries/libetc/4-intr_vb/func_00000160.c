#include "common.h"

static void func_00000160(VBlankFunc *arg0, s32 arg1) {
    s32 i;

    i = arg1 - 1;
    if (arg1 != 0) {
        do {
            *arg0 = 0;
            i--;
            arg0++;
        } while (i != -1);
    }
}
