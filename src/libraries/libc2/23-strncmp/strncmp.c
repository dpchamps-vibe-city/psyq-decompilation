/* Original TU: library-input/psyq/LIB/LIBC2.LIB[23] STRNCMP.OBJ
 * sha256: aab80f4186301b69692026173e39b80003a226afc1c2aa56b111dd04bbc34dbe
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strncmp
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 strncmp(s8 *arg0, s8 *arg1, s32 arg2) {
    s32 n;
    s32 c;

    if ((arg0 == 0) || (arg1 == 0)) {
        if (arg0 == arg1) {
            return 0;
        }
        if (arg0 == 0) {
            return -1;
        }
        return 1;
    }
    n = arg2 - 1;
    while (n >= 0) {
        c = *arg0;
        if (c != *arg1++) {
            break;
        }
        arg0++;
        if (c == 0) {
            return 0;
        }
        n--;
    }
    if (n < 0) {
        return 0;
    }
    return *arg0 - *(arg1 - 1);
}
