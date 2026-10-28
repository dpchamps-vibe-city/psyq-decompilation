#include "common.h"
#include <libpad.h>
#include "libpad-internal.h"

void func_000002BC(PadInfo2 *info) {
    u8 command = info->requestCommand;

    info->requestCommand = 0;
    info->currentCommand = command;
}
