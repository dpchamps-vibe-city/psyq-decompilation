#include "common.h"
#include <libpad-mtap.h>

PadInfo2 *func_000006E4(int port) {
    PadInfo2 *info;

    info = (PadInfo2 *)B_000011C0;
    if (port & 0xF0) {
        info++;
    }
    if (_padModeMtap == 0) {
        return info;
    }
    if ((info->mtapType == 8 && (port & 0xF) == 0) || (port & 3) != 0) {
        info = info->child + (port & 3);
    }
    return info;
}
