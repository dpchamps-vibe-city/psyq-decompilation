/* Original TU: library-input/psyq/LIB/LIBC.LIB[50] MEMCMP.OBJ
 * sha256: b1ed1f35bc336e1fdda8247981cfdeb013e9d48f6c5f7083ba95d49876bce46d
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: memcmp
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

int memcmp(const void *s1, const void *s2, unsigned int n) {
    const u8 *p1 = s1;
    const u8 *p2 = s2;
    s32 i;

    for (i = n - 1; i != -1; i--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}
