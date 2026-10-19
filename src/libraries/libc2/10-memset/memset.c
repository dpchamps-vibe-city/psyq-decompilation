/* MEMSET.OBJ from LIBC2.LIB */
#include "common.h"

void *memset(void *dest, int val, unsigned int len) {
    void *ret;

    if (dest == 0) {
        return 0;
    }
    if ((s32)len <= 0) {
        return 0;
    }
    ret = dest;
    do {
        *(s8 *)dest = val;
        dest += 1;
        len -= 1;
    } while ((s32)len > 0);
    return ret;
}
