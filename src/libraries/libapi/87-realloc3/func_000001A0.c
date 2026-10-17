#include "common.h"

static void *func_000001A0(void *dest, void *source, s32 count) {
    u8 *d;
    u8 *s;

    d = dest;
    s = source;
    if (d >= s) {
        if (count--) {
backward_body:
            d[count] = s[count];
            if (count--) {
                goto backward_body;
            }
        }
    } else {
        if (count--) {
forward_body:
            *d++ = *s++;
            if (count--) {
                goto forward_body;
            }
        }
    }
    return dest;
}
