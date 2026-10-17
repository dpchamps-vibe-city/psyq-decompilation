#include "common.h"

s32 strncmp(s8 *arg0, s8 *arg1, s32 arg2) {
    s32 n;
    s32 c;

    if ((arg0 == 0) || (arg1 == 0)) {
        if (arg0 == arg1) {
            return 0;
        }
        if (arg0 == 0) {
            return -1;
        }
        return 1;
    }
    n = arg2 - 1;
    while (n >= 0) {
        c = *arg0;
        if (c != *arg1++) {
            break;
        }
        arg0++;
        if (c == 0) {
            return 0;
        }
        n--;
    }
    if (n < 0) {
        return 0;
    }
    return *arg0 - *(arg1 - 1);
}
