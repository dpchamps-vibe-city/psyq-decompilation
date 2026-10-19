/* LIBC2.LIB[26] STRRCHR.OBJ */
#include "common.h"

s8 *strrchr(s8 *s, s8 c) {
    s8 *start;

    if (s == 0) {
        return 0;
    }
    start = s;
    do {
        ;
    } while (*s++);
    s -= 1;
    do {
        if (*s == c) {
            return s;
        }
    } while (s-- > start);
    return 0;
}
