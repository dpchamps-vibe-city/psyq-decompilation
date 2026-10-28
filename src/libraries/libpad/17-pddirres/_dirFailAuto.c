#include "common.h"
#include "libpad-internal.h"

void _dirFailAuto(PadInfo2 *info) {
    u8 *recv;

    info->unk4C++;

    switch (info->commandState) {
    case 0:
        break;
    case 1:
        if (info->pad4A[0] < 0xB) {
            info->pad4A[0]++;
        } else {
            info->state = 2;
            info->commandState = 0xFF;
        }
        return;
    default:
        if (info->pad4A[0] < 0xB) {
            info->pad4A[0]++;
            return;
        } else if (info->state != 0) {
            _padFuncClrInfo(info);
        }
        break;
    }

    /* The receive-buffer pointer lives at +0x3C, currently unnamed in the
     * shared record layout (it sits inside pad3A). */
    recv = *(u8 **)(info->pad3A + 2);
    if (recv[0] != 0xF3) {
        info->commandBuffer[0] = 0xFF;
        info->commandBuffer[1] = 0;
        info->mtapType = 0;
        info->pad35[0] = 0;
    }
}
