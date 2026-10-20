#include "common.h"

void parcpy(u8 *dst, u8 *src) {
    s32 i;

    if (src != 0) {
        if (dst != 0) {
            for (i = 0; i < 4; i++) {
                *dst++ = *src++;
            }
        }
    } else if (dst != 0) {
        *dst = 0;
    }
}
