/* Original TU: library-input/psyq/LIB/LIBC2.LIB[9] MEMMOVE.OBJ
 * sha256: e73f7ecc41383ad47586ef991714c7040a62f5564930738d2dceb52898c7be20
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: memmove
 */
#include "common.h"
#include "include_asm.h"

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
