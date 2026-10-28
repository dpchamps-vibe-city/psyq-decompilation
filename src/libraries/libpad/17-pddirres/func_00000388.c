#include "common.h"
#include "libpad-internal.h"
#include <memory.h>

void func_00000388(PadInfo2 *info)
{
    int type;
    int i;
    int active;
    int mask;
    int current;
    int limit;
    u8 *response;
    u8 *data;

    bzero(info->actGate, 6);
    if (info->exId != 0 && info->actTable != NULL) {
        limit = 6;
        if (info->actSize < 7)
            limit = info->actSize;
        for (type = 0; type < info->actAlignCount; type++) {
            active = 0;
            mask = 1;
            if (info->actAlignData[type * 5 + 2] != 0)
                mask = 0xFF;
            response = info->actAlignResponse;
            data = info->actTable;
            for (i = 0; i < limit; response++, i++, data++) {
                if (*response == type && (*data & mask)) {
                    active = 1;
                    break;
                }
            }
            if (active) {
                current = _padTotalCurr + info->actAlignData[type * 5 + 3];
                if (current < 61)
                    _padTotalCurr = current;
                else
                    active = 0;
                if (active) {
                    response = info->actAlignResponse;
                    data = info->actGate;
                    for (i = 0; i < limit; i++, data++) {
                        if (*response++ == type)
                            *data = 1;
                    }
                }
            }
        }
    } else {
        if ((info->mtapType == 4 || info->mtapType == 5 ||
             info->mtapType == 7) &&
            info->exId == 0 && info->actSize >= 2) {
            if ((info->actTable[0] & 0xC0) == 0x40 &&
                (info->actTable[1] & 1) && _padTotalCurr + 10 < 61) {
                info->actGate[1] = 1;
                info->actGate[0] = 1;
                _padTotalCurr += 10;
            }
        } else {
            if (info->mtapType == 3) {
                info->actGate[0] = 1;
                return;
            }
            if (info->exId == 0) {
                for (i = 0; i < 6; i++)
                    info->actGate[i] = 1;
            }
        }
    }
}
