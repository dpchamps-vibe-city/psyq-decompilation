/* library-input/psyq/LIB/LIBC.LIB[48] MEMMOVE.OBJ */
#include "common.h"

void *memmove(void *dest, void *source, int count) {
    char *d;
    char *s;

    d = dest;
    s = source;
    if (d >= s) {
        if (count-- > 0) {
backward_body:
            d[count] = s[count];
            if (count-- > 0) {
                goto backward_body;
            }
        }
    } else {
        if (count-- > 0) {
forward_body:
            *d++ = *s++;
            if (count-- > 0) {
                goto forward_body;
            }
        }
    }
    return d;
}
