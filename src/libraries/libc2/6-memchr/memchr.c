/* Original TU: library-input/psyq/LIB/LIBC2.LIB[6] MEMCHR.OBJ */
#include "common.h"

void *memchr(u8 *s, s32 c, s32 n) {
    if (s == 0) {
        return 0;
    }
    if (n <= 0) {
        return 0;
    }
    while (--n >= 0) {
        if (*s++ == (u8)c) {
            return s - 1;
        }
    }
    return 0;
}
