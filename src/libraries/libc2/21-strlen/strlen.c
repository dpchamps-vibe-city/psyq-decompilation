/* STRLEN.OBJ from LIBC2.LIB */
#include "common.h"

u32 strlen(s8 *s) {
    u32 len = 0;

    if (s == 0) {
        return 0;
    }
    while (*s++) {
        len++;
    }
    return len;
}
