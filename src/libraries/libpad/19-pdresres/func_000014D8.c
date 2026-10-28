#include "common.h"
#include "libpad-internal.h"

void func_000014D8(PadInfo2 *arg0, u8 arg1) {
    arg0->requestCommand = 0x4C;
    (*(u8 **) &arg0->pad2C) = arg0->pad24;
    arg0->pad24[0] = arg1;
    arg0->pad35[1] = 1;
}
