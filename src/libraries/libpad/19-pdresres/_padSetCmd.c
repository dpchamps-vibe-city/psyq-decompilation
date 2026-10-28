#include "common.h"

void _padSetCmd(PadInfo2 *arg0, s32 command, u8 *data, s32 length) {
    arg0->requestCommand = (u8) command;
    (*(u8 **) ((u8 *) arg0 + 0x2C)) = data;
    arg0->pad35[1] = (u8) length;
}
