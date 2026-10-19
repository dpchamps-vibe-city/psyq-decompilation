/* Original TU: library-input/psyq/LIB/LIBC2.LIB[27] STRSPN.OBJ
 * sha256: 0332817fb631646794e8d11e9af2ff567b33bd1aff2c9b64f5507888289c4c24
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strspn
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 strspn(s8 *arg0, s8 *arg1) {
    s8 *start = arg0;
    s8 *q;

    while (*arg0 != 0) {
        for (q = arg1; *q != 0; q++) {
            if (*q == *arg0)
                break;
        }
        if (*q == 0)
            break;
        arg0++;
    }
    return arg0 - start;
}
