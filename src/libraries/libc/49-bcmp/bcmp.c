/* Original TU: library-input/psyq/LIB/LIBC.LIB[49] BCMP.OBJ
 * sha256: 2d85252d036b1b85cb8d15d64e1af65c403f31e3d6719db2a8d96fde0e003188
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: bcmp
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 bcmp(u8 *s1, u8 *s2, s32 n) {
    s32 i;

    for (i = n - 1; i != -1; i--) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}
