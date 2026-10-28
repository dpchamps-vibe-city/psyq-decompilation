#include "common.h"
#include "libpad-internal.h"

void func_00000160(PadInfo2 *info) {
    int i;
    u8 fill;
    u8 *p;

    if (info->state == 0)
        return;

    info->state = 0;
    info->commandState = 0;
    info->exId = 0;
    info->prepareCommand = 0;
    info->applyResponse = 0;
    info->idCount = 0;
    info->prevMode = 0;
    info->exId = 0;
    info->actAlignCount = 0;
    info->padEA[0] = 0;
    info->idTable = 0;
    info->actAlignData = 0;
    info->combTable = 0;
    p = info->actAlignResponse;
    fill = 0xFF;
    i = 5;
    do {
        *p++ = fill;
    } while (--i >= 0);
}
