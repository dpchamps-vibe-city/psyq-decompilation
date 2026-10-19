/* STRSTR.OBJ from LIBC2.LIB */
#include "common.h"

s8 *strstr(s8 *s1, s8 *s2) {
    s8 *p;
    s8 *q;
    s8 *start;
    s32 matched;

    p = s1;
    matched = 0;
    q = s2;
    start = s1;
    while (*p != 0) {
        if (*p == *q) {
            q++;
            if (*q == 0) {
                return start;
            }
            if (matched == 0) {
                start = p;
                matched = 1;
            }
        } else {
            q = s2;
            matched = 0;
        }
        p++;
    }
    return 0;
}
