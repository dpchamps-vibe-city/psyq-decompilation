#include "common.h"
#include <libpad.h>

extern s32 _padCalledIntPad;

int PadChkVsync(void) {
    s32 temp_v0;

    temp_v0 = _padCalledIntPad;
    _padCalledIntPad = 0;
    return temp_v0;
}
