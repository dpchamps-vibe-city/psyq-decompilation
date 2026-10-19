/* Original TU: library-input/psyq/LIB/LIBC2.LIB[22] STRNCAT.OBJ
 * sha256: ea0f654503e614b6015582a820de31ee828b7c2e8e902d670fb1d48d8ecabe1f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strncat
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s8 *strncat(s8 *arg0, u8 *arg1, s32 arg2) {
    s8 *save;
    u8 c;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }
    save = arg0;
    while (*arg0++ != 0) {
    }
    arg0 -= 1;
    for (;;) {
        c = *arg1++;
        *arg0++ = c;
        if (c == 0) {
            break;
        }
        if (--arg2 < 0) {
            arg0[-1] = 0;
            break;
        }
    }
    return save;
}
