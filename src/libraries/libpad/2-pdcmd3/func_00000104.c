#include "common.h"
#include "libpad-internal.h"

static void func_00000104(PadInfo2 *info) {
    int command;
    unsigned char *data;
    int length;

    switch (info->commandState) {
    case 2:
        command = 0x44;
        data = &info->mode;
        length = 2;
        break;
    case 3:
        command = 0x4D;
        data = info->actAlignResponse;
        length = 6;
        break;
    default:
        return;
    }
    _padSetCmd(info, command, data, length);
}
