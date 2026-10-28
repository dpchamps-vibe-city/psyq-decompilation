#include "common.h"
#include "libpad-internal.h"

extern int _padRecvAtLoadInfo(PadInfo2 *);

#define rxFrame ((vu8 *)(*(u8 **)&info->pad3A[2]))
#define rxCount (info->pad3A[0xA])

static void func_00000734(PadInfo2 *info) {
    u8 oldType;
    u8 type;
    int i;

    if ((rxFrame[0] & 0xF0) == 0) {
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0;
        info->mtapType = 0;
        info->pad35[0] = 0;
        _padFuncClrInfo(info);
        return;
    }

    oldType = info->mtapType;
    type = rxFrame[0] >> 4;
    info->mtapType = type;
    if (type == 0xF) {
        info->mtapType = oldType;
    } else {
        info->commandBuffer[0] = 0;
        info->commandBuffer[1] = rxFrame[0];
        info->pad35[0] = rxCount;
        for (i = 2; i < rxCount; i++) {
            info->commandBuffer[i] = rxFrame[i];
        }
    }

    if ((rxFrame[1] == 0
         && (info->commandState != 1 || info->prepareCommand != 0)
         && info->pad50 == 0)
        || info->mtapType != oldType) {
        _padFuncClrInfo(info);
    }

    info->pad4A[0] = 0;
    if (info->commandState == 0xFF) {
        return;
    }
    if (info->commandState != 0 && info->requestCommand == 0) {
        return;
    }
    if ((u8)(info->commandState - 2) < 0xFC && rxFrame[0] != 0xF3) {
        _padFuncClrInfo(info);
        return;
    }

    switch (info->commandState) {
    case 0:
        info->state = 1;
        info->commandState++;
        break;
    case 1:
        info->pad47[0] = 0;
        info->commandState++;
        break;
    case 0xFE:
        info->commandState = 0xFF;
        break;
    default:
        if (info->applyResponse != 0) {
            info->commandState += info->applyResponse(info);
        } else {
            info->commandState += _padRecvAtLoadInfo(info);
        }
        break;
    }
}
