#include "common.h"
#include "libpad-internal.h"

int func_00000A80(PadInfo2 *info) {
    if (info->exId != 0) {
        int state = 0xFF;
        if (info->commandState != state) {
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}
