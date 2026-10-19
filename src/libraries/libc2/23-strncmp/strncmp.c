/* STRNCMP.OBJ from LIBC2.LIB */
#include "common.h"

s32 strncmp(s8 *s1, s8 *s2, s32 n) {
    s32 m;
    s32 c;

    if ((s1 == 0) || (s2 == 0)) {
        if (s1 == s2) {
            return 0;
        }
        if (s1 == 0) {
            return -1;
        }
        return 1;
    }
    m = n - 1;
    while (m >= 0) {
        c = *s1;
        if (c != *s2++) {
            break;
        }
        s1++;
        if (c == 0) {
            return 0;
        }
        m--;
    }
    if (m < 0) {
        return 0;
    }
    return *s1 - *(s2 - 1);
}
