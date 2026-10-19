/* BZERO.OBJ from LIBC2.LIB */
#include "common.h"

void *bzero(void *dst, s32 len) {
    void *save_dst;

    if (dst == 0) {
        return 0;
    }
    if (len <= 0) {
        return 0;
    }
    save_dst = dst;
    do {
        *(s8 *)dst = 0;
        dst += 1;
        len -= 1;
    } while (len > 0);
    return save_dst;
}
