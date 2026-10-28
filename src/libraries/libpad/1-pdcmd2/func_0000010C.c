#include "common.h"
#include "libpad-internal.h"

static int func_0000010C(PadInfo2 *info) {
    int i;
    int j;
    int count;
    int min;
    u8 *map;

    for (i = 0; i < info->actAlignCount; i++) {
        map = info->commandTable;
        count = 0;
        for (j = 0; j < 6; j++) {
            if (*map++ == i) {
                count++;
            }
        }
        min = info->actAlignData[i * 5 + 2];
        map = info->commandTable;
        if (min == 0) {
            min = 1;
        }
        for (j = 0; j < 6; j++) {
            if (*map++ == i) {
                if (count < min) {
                    info->actAlignResponse[j] = 0xFF;
                    count--;
                } else {
                    info->actAlignResponse[j] = i;
                }
            }
        }
    }
    info->commandState = 0xFE;
    return 0;
}
