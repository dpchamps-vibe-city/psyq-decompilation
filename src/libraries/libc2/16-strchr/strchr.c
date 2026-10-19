/* Original TU: library-input/psyq/LIB/LIBC2.LIB[16] STRCHR.OBJ */
#include "common.h"

s8 *strchr(s8 *s, s32 c) {
    s8 ch = c;
    s32 cur;

    if (s == 0) {
        return 0;
    }
    do {
        cur = *s;
        if (cur == ch) {
            return s;
        }
        s++;
    } while (cur != 0);
    return 0;
}
