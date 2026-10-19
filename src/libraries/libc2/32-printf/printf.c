/* Original TU: library-input/psyq/LIB/LIBC2.LIB[32] PRINTF.OBJ
 * sha256: d8f605926eccb543e4d2d046f74d9c5c4b310616514ab5918cfdd398f14cc36a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: printf
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern int prnt();

int printf(const char *fmt, int a1, int a2, int a3) {
    int *ap = &a1;

    (void)&fmt;
    ap[1] = a2;
    ap[2] = a3;
    return prnt(1, fmt, ap);
}
