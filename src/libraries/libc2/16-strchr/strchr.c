#include "common.h"

s8 *strchr(s8 *arg0, s32 arg1) {
    s8 ch = arg1;
    s32 c;

    if (arg0 == 0) {
        return 0;
    }
    do {
        c = *arg0;
        if (c == ch) {
            return arg0;
        }
        arg0++;
    } while (c != 0);
    return 0;
}
