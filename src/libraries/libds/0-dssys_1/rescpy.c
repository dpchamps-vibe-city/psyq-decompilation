#include "common.h"

void rescpy(u8 *dst, u8 *src) {
    s32 i;
    u8 c;

    if (src != 0) {
        i = 0;
        if (dst != 0) {
            do {
                c = *src;
                src += 1;
                i += 1;
                *dst = c;
                dst += 1;
            } while (i < 8);
        }
    } else if (dst != 0) {
        *dst = 0;
    }
}
