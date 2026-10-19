/* Original TU: library-input/psyq/LIB/LIBC2.LIB[26] STRRCHR.OBJ
 * sha256: d06274a9e2acba0a6c4c51a51d37f205404b45030ac3b182040b48ab363437c2
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strrchr
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s8 *strrchr(s8 *s, s8 c) {
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
