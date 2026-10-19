/* Original TU: library-input/psyq/LIB/LIBC2.LIB[2] BZERO.OBJ
 * sha256: 7cd6c53977f8ccc700d353280dc961a33f8eb1f7bd47e3f5c0c2e2ee0808003a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: bzero
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

void *bzero(void *arg0, s32 arg1) {
    void *var_v0;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 <= 0) {
        return 0;
    }
    var_v0 = arg0;
    do {
        *(s8 *)arg0 = 0;
        arg0 += 1;
        arg1 -= 1;
    } while (arg1 > 0);
    return var_v0;
}
