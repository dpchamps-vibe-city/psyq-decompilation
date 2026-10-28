#include "common.h"
#include "libpad-internal.h"

int _padGetActSize(PadInfo2 *);
static s32 _padLoadActInfo(PadInfo2 *, u8 *);

s32 _padRecvAtLoadInfo(PadInfo2 *info) {
    u16 id;
    u8 phase;
    int actSize;

    switch (info->commandState) {
    case 2:
        if (info->data3C[7] != 0) {
            return 0;
        }
        if (info->idCount == info->data3C[3] && info->prevMode == info->data3C[4]
            && info->actAlignCount == info->data3C[5]
            && info->padEA[0] == info->data3C[6]) {
            *(u16 *)&info->padEA[4] = 0;
        } else {
            *(u16 *)&info->padEA[4] = 0xFFFF;
        }
        info->idCount = info->data3C[3];
        info->prevMode = info->data3C[4];
        info->exId = 0;
        info->actAlignCount = info->data3C[5];
        info->padEA[0] = info->data3C[6];
        *(u16 *)&info->padEA[2] = 0;
        if (*(u16 *)&info->padEA[4] != 0) {
            return 0;
        }
        info->padEA[1] = 0;
        break;
    case 3:
        if (info->data3C[2] != 0 || info->data3C[3] != 0) {
            return 0;
        }
        id = (info->data3C[4] << 8) + info->data3C[5];
        info->exId = id;
        if (*(u16 *)&info->padEA[4] != id) {
            *(u16 *)&info->padEA[4] = id;
            return 0;
        }
        *(u16 *)&info->padEA[4] = 0xFFFF;
        info->padEA[1] = 0;
        info->pad47[0] = 0;
        break;
    case 4:
        if (info->data3C[2] != 0 || info->data3C[3] != 0) {
            return 0;
        }
        actSize = *(u16 *)&info->padEA[2] + 8;
        *(u16 *)&info->padEA[2] = actSize + ((info->data3C[4] + 3) & 0x1FC);
        phase = info->pad47[0] + 1;
        info->pad47[0] = phase;
        if (phase < info->padEA[0]) {
            return 0;
        }
        if (_padGetActSize(info) >= 0x81) {
            _padFuncClrInfo(info);
            info->commandState = 0xFE;
            info->state = 2;
        } else {
            if (*(u16 *)&info->padEA[4] != *(u16 *)&info->padEA[2]) {
                *(u16 *)&info->padEA[4] = *(u16 *)&info->padEA[2];
                info->pad47[0] = 0;
                *(u16 *)&info->padEA[2] = 0;
                return 0;
            }
            *(u16 *)&info->padEA[4] = 0;
            info->padEA[1] = 0;
            info->commandState = 0xFF;
            _padLoadActInfo(info, info->pad63);
            info->commandState = 2;
        }
        return 0;
    }
    return 1;
}
