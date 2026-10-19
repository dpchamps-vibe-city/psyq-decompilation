/* Original TU: library-input/psyq/LIB/LIBC2.LIB[16] STRCHR.OBJ
 * sha256: ddf8488eb361d84a2b2dfe790b989ceb3cd59d60ac7b328504a0b90b1cc0460b
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strchr
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s8 *strchr(s8 *arg0, s32 arg1) {
    s8 ch = arg1;
    s32 c;

    if (arg0 == 0) {
        return 0;
    }
    do {
        c = *arg0;
        if (c == ch) {
            return arg0;
        }
        arg0++;
    } while (c != 0);
    return 0;
}
