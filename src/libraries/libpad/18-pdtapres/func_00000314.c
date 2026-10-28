#include "common.h"
#include "libpad-internal.h"

void func_00000314(PadInfo2 *info) {
    PadInfo2 *child;
    u8 command;
    int i;

    command = info->requestCommand;
    child = info->child;
    info->requestCommand = 0;
    info->currentCommand = command;
    for (i = 0; i < 4; i++, child++) {
        child->previousCommand = child->currentCommand;
        child->currentCommand = child->requestCommand;
        child->requestCommand = 0;
    }
}
