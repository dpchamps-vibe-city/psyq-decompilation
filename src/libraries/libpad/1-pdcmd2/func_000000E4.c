#include "common.h"
#include "libpad-internal.h"

static void func_000000E4(PadInfo2 *info) {
    _padSetCmd(info, 0x4D, info->commandTable, 6);
}
