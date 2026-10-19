/* BCOPY.OBJ from LIBC2.LIB */
#include "common.h"

u8 *bcopy(u8 *src, u8 *dest, s32 len) {
    u8 *save_src;

    if (src == 0) {
        return 0;
    }
    save_src = src;
    if (len > 0) {
        do {
            *dest = *src;
            src++;
            len--;
            dest++;
        } while (len > 0);
    }
    return save_src;
}
