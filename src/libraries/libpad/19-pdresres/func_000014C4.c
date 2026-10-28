#include "common.h"
#include "libpad-internal.h"

void func_000014C4(PadInfo2 *arg0) {
    arg0->requestCommand = 0x45;
    (*(u8 **) &arg0->pad2C) = NULL;
    arg0->pad35[1] = 0;
}
