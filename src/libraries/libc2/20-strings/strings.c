/* Original TU: library-input/psyq/LIB/LIBC2.LIB[20] STRINGS.OBJ
 * sha256: 08456701a2c5e461d1d5292e2e68a842ddb754497367d30faf0941c7d5e80498
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: index, rindex
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s8 *index(s8 *s, s8 c) {
    s8 ch;

    if (s != 0) {
        for (;;) {
            ch = *s;
            if (ch == c) {
                goto found;
            }
            if (ch == 0) {
                return 0;
            }
            s += 1;
        }
    }
    return 0;
found:
    return s;
}
#include "common.h"

s8 *rindex(s8 *s, s8 c) {
    s8 *start;

    if (s == 0) {
        return 0;
    }
    start = s;
    do {
        ;
    } while (*s++);
    s -= 1;
    do {
        if (*s == c) {
            return s;
        }
    } while (s-- > start);
    return 0;
}
