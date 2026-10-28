#include "common.h"
#include <memory.h>

PadInfo2 *func_00000604(s32 port) {
    PadInfo2 *var_v0;

    var_v0 = B_00000AC0;
    if (port & 0xF0) {
        var_v0 = &B_00000AC0[1];
    }
    return var_v0;
}
