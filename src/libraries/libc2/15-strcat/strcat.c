/* Original TU: library-input/psyq/LIB/LIBC2.LIB[15] STRCAT.OBJ */
#include "common.h"

extern u32 strlen(s8 *);

s8 *strcat(s8 *dst, s8 *src) {
    s8 *dst_start;
    u8 c;

    if (dst == 0) {
        return 0;
    }
    if (src == 0) {
        return 0;
    }
    /* PSYQ strcat rejects overlapping strings (ends at same address). */
    if (dst + strlen(dst) != src + strlen(src)) {
        dst_start = dst;
        while (*dst++ != 0) {
        }
        dst -= 1;
        do {
            c = *(u8 *)src;
            src += 1;
            *dst = (s8)c;
            dst += 1;
        } while (c != 0);
        return dst_start;
    }
    return 0;
}
