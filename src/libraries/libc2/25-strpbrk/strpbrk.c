/* Original TU: library-input/psyq/LIB/LIBC2.LIB[25] STRPBRK.OBJ
 * sha256: ecb7d82f15646784a182e2128cabe35171ef212462574f10ba30e62952e6c731
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strpbrk
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s8 *strpbrk(s8 *arg0, s8 *arg1) {
    s8 *start = arg0;
    s8 *q;
    s8 *ret;

    while (*arg0 != 0) {
        for (q = arg1; *q != 0; q++) {
            if (*q == *arg0)
                return arg0;
        }
        arg0++;
    }
    ret = (s8 *)*arg0;
    if (start == arg0)
        ret = 0;
    return ret;
}
