#include "common.h"

static void func_00000134(s32 arg0, VBlankFunc arg1) {
    if (arg1 != D_00000190[arg0]) {
        D_00000190[arg0] = arg1;
    }
}
