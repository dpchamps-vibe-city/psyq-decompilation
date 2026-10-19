/* LIBC2.LIB STRCSPN.OBJ */
#include "common.h"

s32 strcspn(s8 *s, s8 *reject) {
    s8 *start = s;
    s8 *p;

    while (*s != 0) {
        for (p = reject; *p != 0; p++) {
            if (*p == *s)
                break;
        }
        if (*p != 0)
            break;
        s++;
    }
    return s - start;
}
