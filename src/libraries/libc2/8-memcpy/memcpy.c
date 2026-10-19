/* library-input/psyq/LIB/LIBC2.LIB[8] MEMCPY.OBJ */
#include "common.h"

void *memcpy(void *dest, const void *src, unsigned int len) {
    void *ret;

    if (dest == 0) {
        return 0;
    }
    ret = dest;
    while ((s32)len > 0) {
        *(u8 *)dest = *(u8 *)src;
        dest += 1;
        src += 1;
        len -= 1;
    }
    return ret;
}
