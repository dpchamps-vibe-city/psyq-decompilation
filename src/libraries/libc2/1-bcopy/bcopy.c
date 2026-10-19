/* Original TU: library-input/psyq/LIB/LIBC2.LIB[1] BCOPY.OBJ
 * sha256: 4edbfed0f2fbd9b874ad2e576633043de7f97b4da5f8122875f6c2a4fe00fe64
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: bcopy
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

u8 *bcopy(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *temp_v1;

    if (arg0 == 0) {
        return 0;
    }
    temp_v1 = arg0;
    if (arg2 > 0) {
        do {
            *arg1 = *arg0;
            arg0++;
            arg2--;
            arg1++;
        } while (arg2 > 0);
    }
    return temp_v1;
}
