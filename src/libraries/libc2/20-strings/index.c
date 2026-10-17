#include "common.h"

s8 *index(s8 *s, s8 c) {
    s8 ch;

    if (s != 0) {
        for (;;) {
            ch = *s;
            if (ch == c) {
                goto found;
            }
            if (ch == 0) {
                return 0;
            }
            s += 1;
        }
    }
    return 0;
found:
    return s;
}
