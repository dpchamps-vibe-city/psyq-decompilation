#include "common.h"

void _padCmdParaMode(PadInfo2 *arg0, s32 mode) {
    arg0->requestCommand = 0x43;
    (*(u8 **) ((u8 *) arg0 + 0x2C)) = arg0->pad24;
    arg0->pad24[0] = (u8) mode;
    arg0->pad35[1] = 1;
}
