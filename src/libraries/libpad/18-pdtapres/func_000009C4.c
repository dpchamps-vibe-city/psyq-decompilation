#include "common.h"
#include "libpad-internal.h"

extern int _padRecvAtLoadInfo(PadInfo2 *);
extern void _mtapFailAuto(PadInfo2 *, int);

static void func_000009C4(PadInfo2 *info) {
    PadInfo2 *child;
    u8 *src;
    u8 *dst;
    u8 oldType;
    int type;
    int hdr;
    int i;

    hdr = info->data3C[0];
    hdr &= 0xF0;
    if (hdr == 0) {
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0;
        info->mtapType = 0;
        info->pad35[0] = 0;
        _padFuncClrInfo(info);
        return;
    }

    if (info != info->root) {
        if ((info->data3C[1] != 0 && info->data3C[1] != 0x5A)
            || (info->data3C[0] >> 4) == 8) {
            _mtapFailAuto(info, 0xFF);
            return;
        }
    }

    oldType = info->mtapType;
    dst = info->commandBuffer;
    type = info->data3C[0] >> 4;
    if (info->data3C[1] == 0x5A) {
        if (oldType == 8) {
            *dst = 0;
        } else if (type != 0xF) {
            info->mtapType = type;
            src = info->data3C;
            *dst++ = 0;
            *dst++ = *src++;
            if (info != info->root) {
                info->pad35[0] = 8;
                src++;
                for (i = 2; i < 8; i++) {
                    *dst++ = *src++;
                }
            } else if (type == 8) {
                info->pad35[0] = 2;
            } else {
                info->pad35[0] = info->pad44[0];
                src++;
                for (i = 2; i < info->pad35[0]; i++) {
                    *dst++ = *src++;
                }
            }
        }
    }

    if ((info->data3C[1] == 0
         && (info->commandState != 1 || info->prepareCommand != 0)
         && info->pad50 == 0)
        || info->mtapType != oldType) {
        _padFuncClrInfo(info);
    }

    if (info->child != 0 || info->requestCommand == 0) {
        info->pad4A[0] = 0;
    }
    if (info->commandState == 0xFF) {
        return;
    }
    if ((u8)(info->commandState - 2) < 0xFC && info->data3C[0] != 0xF3) {
        _padFuncClrInfo(info);
        return;
    }

    if (info->mtapType == 8) {
        if (info->commandState != 0) {
            info->commandState++;
            return;
        }
    } else if (info->commandState != 0) {
        if (info == info->root) {
            if (info->requestCommand == 0) {
                return;
            }
        } else if (info->currentCommand == 0) {
            return;
        }
    }

    switch (info->commandState) {
    case 0:
        child = info->child;
        if (child != 0 || info->requestCommand == 0) {
            if (info->mtapType == 8 && child != 0 && child->data3C[0] == 0xFF) {
                info->state = 2;
                info->commandState = 0xFF;
            } else {
                info->state = 1;
                info->commandState++;
            }
        }
        break;
    case 1:
        info->pad47[0] = 0;
        info->commandState++;
        break;
    case 0xFE:
        info->commandState++;
        break;
    case 0xFF:
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
