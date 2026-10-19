/* Original TU: library-input/psyq/LIB/LIBC2.LIB[17] STRCMP.OBJ */
#include "common.h"

int strcmp(const char *s1, const char *s2) {
    u8 c;
    if ((s1 == 0) || (s2 == 0)) {
        if (s1 == s2) {
            return 0;
        }
        if (s1 == 0) {
            return -1;
        }
        return 1;
    }
    goto body;
exit_loop:
    return 0;
test:
    if (c == 0) {
        goto exit_loop;
    }
    s1++;
body:
    c = *s1;
    if (*(const s8 *)s1 != *(const s8 *)s2++) {
        s1++;
        return *(const s8 *)(s1 - 1) - *(const s8 *)(s2 - 1);
    }
    goto test;
}
