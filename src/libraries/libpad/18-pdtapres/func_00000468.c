#include "common.h"
#include <memory.h>
#include "libpad-internal.h"

/* PDMTAPRES task limit accumulated while act-align entries are applied. */
extern int _padTotalCurr;

void func_00000468(PadInfo2 *info) {
    int i;
    int j;
    int limit;
    int mask;
    int found;
    int total;
    u8 *response;
    u8 *table;
    u8 *resp;
    u8 *flag;

    bzero(&info->pad54[3], 6);
    if (info->exId != 0 && info->actTable != 0) {
        limit = 6;
        if (info->actSize < 7) {
            limit = info->actSize;
        }
        for (i = 0; i < info->actAlignCount; i++) {
            found = 0;
            mask = 1;
            if (info->actAlignData[i * 5 + 2]) {
                mask = 0xFF;
            }
            response = info->actAlignResponse;
            table = info->actTable;
            for (j = 0; j < limit; j++) {
                if (*response == i && (*table & mask)) {
                    found = 1;
                    break;
                }
                response++;
                table++;
            }
            if (found) {
                total = _padTotalCurr + info->actAlignData[i * 5 + 3];
                if (total < 0x3D) {
                    _padTotalCurr = total;
                } else {
                    found = 0;
                }
                if (found) {
                    resp = info->actAlignResponse;
                    flag = &info->pad54[3];
                    for (j = 0; j < limit; j++) {
                        if (*resp++ == i) {
                            *flag = 1;
                        }
                        flag++;
                    }
                }
            }
        }
    } else if ((info->mtapType == 4 || info->mtapType == 5 || info->mtapType == 7) && info->exId == 0 && info->actSize >= 2) {
        if ((info->actTable[0] & 0xC0) == 0x40 && (info->actTable[1] & 1) && _padTotalCurr + 0xA < 0x3D) {
            info->pad54[4] = 1;
            info->pad54[3] = 1;
            _padTotalCurr += 0xA;
        }
    } else if (info->mtapType == 3) {
        info->pad54[3] = 1;
    } else if (info->exId == 0) {
        for (j = 0; j < 6; j++) {
            info->pad54[j + 3] = 1;
        }
    }
}
