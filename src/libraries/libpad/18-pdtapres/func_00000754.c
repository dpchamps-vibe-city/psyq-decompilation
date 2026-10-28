#include "common.h"
#include "libpad-mtap.h"

int func_00000754(PadInfo2 *info)
{
    PadInfo2 *child;
    int i;

    if (info->child == 0) {
        if (info->currentCommand != 0) {
            if (_mtapLastResult[_padSioChan] != 0 && info->currentCommand != 0x43) {
                info->requestCommand = info->currentCommand;
                info->currentCommand = 0;
            }
            return 0;
        }
        child = info->root->child;
        for (i = 0; i < 4; i++, child++) {
            if ((child->requestCommand == 0x43 || child->currentCommand == 0x43) &&
                **(u8 **)&child->pad2C == 1) {
                return 0;
            }
        }
    }
    if (*info->data3C == 0xF3 &&
        (info->mtapType == 0 || (info->commandState == 0xFF && info->state != 2))) {
        _padCmdParaMode(info, 0);
        return 0;
    }
    if (*info->data3C == 0xF3 && info->state == 2 && info->mtapType != 8) {
        _padFuncClrInfo(info);
        return 0;
    }
    switch (info->commandState) {
    case 1:
        _padCmdParaMode(info, 1);
        break;
    case 0xFF:
        if (info->mtapType == 8 && info->child != 0) {
            child = info->child;
            for (i = 0; i < 4; i++, child++) {
                if (child->commandState == 1) {
                    func_00000754(child);
                    return 0;
                }
            }
            return 1;
        }
        break;
    case 0:
        break;
    case 0xFE:
        if (info->state != 2) {
            _padCmdParaMode(info, 0);
        } else {
            info->requestCommand = 0;
        }
        break;
    default:
        if (info->prepareCommand != 0) {
            info->prepareCommand(info);
        } else {
            _padSendAtLoadInfo(info);
        }
        break;
    }
    return 0;
}
