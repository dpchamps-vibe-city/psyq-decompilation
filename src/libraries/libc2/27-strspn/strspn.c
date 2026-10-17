#include "common.h"

s32 strspn(s8 *arg0, s8 *arg1) {
    s8 *start = arg0;
    s8 *q;

    while (*arg0 != 0) {
        for (q = arg1; *q != 0; q++) {
            if (*q == *arg0)
                break;
        }
        if (*q == 0)
            break;
        arg0++;
    }
    return arg0 - start;
}
