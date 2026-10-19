/* LIBC2.LIB STRPBRK.OBJ */
#include "common.h"

s8 *strpbrk(s8 *s, s8 *accept) {
    s8 *start = s;
    s8 *p;
    s8 *ret;

    while (*s != 0) {
        for (p = accept; *p != 0; p++) {
            if (*p == *s)
                return s;
        }
        s++;
    }
    ret = (s8 *)*s;
    if (start == s)
        ret = 0;
    return ret;
}
