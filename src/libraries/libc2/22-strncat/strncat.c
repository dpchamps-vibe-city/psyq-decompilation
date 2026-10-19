/* STRNCAT.OBJ from LIBC2.LIB */
#include "common.h"

s8 *strncat(s8 *dst, u8 *src, s32 n) {
    s8 *dst_start;
    u8 c;

    if (dst == 0) {
        return 0;
    }
    if (src == 0) {
        return 0;
    }
    dst_start = dst;
    while (*dst++ != 0) {
    }
    dst -= 1;
    for (;;) {
        c = *src++;
        *dst++ = c;
        if (c == 0) {
            break;
        }
        if (--n < 0) {
            dst[-1] = 0;
            break;
        }
    }
    return dst_start;
}
