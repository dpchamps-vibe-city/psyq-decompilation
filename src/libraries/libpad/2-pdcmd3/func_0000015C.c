#include "common.h"
#include "libpad-internal.h"

static int func_0000015C(PadInfo2 *info) {
    if (info->modeEqual != 0) {
        if (info->commandState == 2) {
            return 1;
        }
        info->commandState = 0xFE;
        return 0;
    }
    _padFuncClrInfo(info);
    return 0;
}
