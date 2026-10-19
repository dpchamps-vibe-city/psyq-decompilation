/* Original TU: library-input/psyq/LIB/LIBC2.LIB[24] STRNCPY.OBJ
 * sha256: ea44e99696475ece4caaa40e0c4b23338524262f7fdacf3467aea31277081eea
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strncpy
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

u8 *strncpy(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *save;
    u8 *var_v0;
    s32 i;
    u8 c;

    var_v0 = 0;
    if (arg0 != 0) {
        i = 0;
        if (arg1 != 0) {
            save = arg0;
            if (arg2 > 0) {
                for (;;) {
                    c = *arg1++;
                    *arg0++ = c;
                    if (c == 0) {
                        i += 1;
                        while (i < arg2) {
                            *arg0++ = 0;
                            i += 1;
                        }
                        return save;
                    }
                    i += 1;
                    if (i >= arg2) {
                        break;
                    }
                }
            }
            var_v0 = save;
        }
    }
    return var_v0;
}
