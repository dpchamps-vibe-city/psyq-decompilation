#include "common.h"
#include "libpad-mtap.h"

void _mtapFailAuto(PadInfo2 *info, int result) {
    PadInfo2 *child;
    int type;
    int i;

    type = info->data3C[0] >> 4;
    if (info->mtapType != 8 && type == 8 && info == info->root) {
        info->mtapType = type;
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0x80;
        info->pad35[0] = 2;
    }
    if (info->mtapType == 8) {
        child = info->child;
        if (child != 0) {
            for (i = 0; i < 4; i++) {
                _mtapFailAuto(child++, -1);
            }
        }
    }
    child = info->root->child;
    if (info->child != 0) {
        if (info->requestCommand == 0) {
            if ((child++)->currentCommand != 0 ||
                (child++)->currentCommand != 0 ||
                (child++)->currentCommand != 0 ||
                (child++)->currentCommand != 0) {
                if (info->pad4A[0] == 0)
                    info->pad4A[0] = 1;
                return;
            }
        }
    }
    child = info->root->child;
    if (info->child == 0 && info->currentCommand == 0) {
        if (info->root->requestCommand != 0 ||
            (child++)->currentCommand != 0 ||
            (child++)->currentCommand != 0 ||
            (child++)->currentCommand != 0 ||
            (child++)->currentCommand != 0) {
            if (info->pad4A[0] == 0)
                info->pad4A[0] = 1;
            return;
        }
    }

    info->unk4C++;
    info->previousCommand = info->currentCommand;
    info->currentCommand = info->requestCommand;
    info->requestCommand = 0;
    switch (info->commandState) {
    case 0:
        break;
    case 1:
        if (info->pad4A[0] < 0xB && info->mtapType != 8) {
            info->pad4A[0]++;
            return;
        }
        if (info->exId != 0) {
            if (info->pad4A[0] < 0x15) {
                info->pad4A[0]++;
                return;
            }
            _padFuncClrInfo(info);
        }
        info->state = 2;
        if (info->mtapType != 8) {
            if (info->child != 0) {
                info->currentCommand = 0;
                info->requestCommand = 0;
            }
            info->commandState = 0xFF;
        } else {
            info->commandState = 0xFE;
        }
        return;
    default:
        if (info->pad4A[0] < 0xB) {
            info->pad4A[0]++;
            return;
        }
        break;
    }
    if (info->state != 0) {
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0;
        info->mtapType = 0;
        info->pad35[0] = 0;
        _padFuncClrInfo(info);
    }
    if (type != 8) {
        if (info->mtapType == 8) {
            info->mtapType = 0;
            info->commandBuffer[1] = 0;
        }
    } else if (info->child != 0) {
        info->mtapType = type;
        info->commandBuffer[1] = 0x80;
    }
}
