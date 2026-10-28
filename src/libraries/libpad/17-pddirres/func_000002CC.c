#include "common.h"
#include "libpad-internal.h"

u8 func_000002CC(PadInfo2 *info) {
    int index;
    u8 *data;

    index = info->pad44[1] - 3;
    switch (info->requestCommand) {
    case 0:
        if (index < 6 && info->pad54[3 + index] == 0) {
            return 0;
        }
        return index < info->actSize ? info->actTable[index] : 0;
    case 0x4D:
        return index < info->pad35[1] ? (*(u8 **)&info->pad2C)[index] : 0xFF;
    default:
        return index < info->pad35[1] ? (*(u8 **)&info->pad2C)[index] : 0;
    }
}
