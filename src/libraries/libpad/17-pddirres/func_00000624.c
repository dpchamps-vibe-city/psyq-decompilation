#include "common.h"
#include <libpad.h>
#include "libpad-direct.h"

extern void _padCmdParaMode(PadInfo2 *, int mode);
extern void _padSendAtLoadInfo(PadInfo2 *);

int func_00000624(PadInfo2 *info) {
    if (info->data3C[0] == 0xF3) {
        if (info->mtapType == 0) {
            _padCmdParaMode(info, 0);
            return 0;
        }
        if (info->commandState == 0xFF) {
            _padCmdParaMode(info, 0);
            return 0;
        }
        if (info->state == PadStateFindCTP1)
            _padFuncClrInfo(info);
    }
    switch (info->commandState) {
    case 0:
        break;
    case 1:
        _padCmdParaMode(info, 1);
        break;
    case 0xFE:
        _padCmdParaMode(info, 0);
        break;
    case 0xFF:
        break;
    default:
        if (info->prepareCommand != NULL)
            info->prepareCommand(info);
        else
            _padSendAtLoadInfo(info);
        break;
    }
    return 0;
}
