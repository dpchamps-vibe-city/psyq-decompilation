#include "common.h"

s8 *strncat(s8 *arg0, u8 *arg1, s32 arg2) {
    s8 *save;
    u8 c;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }
    save = arg0;
    while (*arg0++ != 0) {
    }
    arg0 -= 1;
    for (;;) {
        c = *arg1++;
        *arg0++ = c;
        if (c == 0) {
            break;
        }
        if (--arg2 < 0) {
            arg0[-1] = 0;
            break;
        }
    }
    return save;
}
