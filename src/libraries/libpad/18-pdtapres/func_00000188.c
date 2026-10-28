#include "common.h"
#include "libpad-internal.h"

static void func_00000188(PadInfo2 *info) {
    int i;
    u8 *response;

    if (info->state) {
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
        *(u32 *)info->pad08 = 0;
        info->requestCommand = 0;
        info->currentCommand = 0;
        info->previousCommand = 0;
        response = info->actAlignResponse;
        for (i = 0; i < 6; i++) {
            *response++ = 0xFF;
        }
    }
}
