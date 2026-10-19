/* LIBC2.LIB STRSPN.OBJ */
#include "common.h"

s32 strspn(s8 *s, s8 *accept) {
    s8 *start = s;
    s8 *q;

    while (*s != 0) {
        for (q = accept; *q != 0; q++) {
            if (*q == *s)
                break;
        }
        if (*q == 0)
            break;
        s++;
    }
    return s - start;
}
