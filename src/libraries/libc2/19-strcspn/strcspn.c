/* Original TU: library-input/psyq/LIB/LIBC2.LIB[19] STRCSPN.OBJ
 * sha256: 78c3f96936dbe90afc71ad40a38e57e94309cd1c251b3ae623a41f126cfd4b25
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strcspn
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 strcspn(s8 *arg0, s8 *arg1) {
    s8 *start = arg0;
    s8 *q;

    while (*arg0 != 0) {
        for (q = arg1; *q != 0; q++) {
            if (*q == *arg0)
                break;
        }
        if (*q != 0)
            break;
        arg0++;
    }
    return arg0 - start;
}
