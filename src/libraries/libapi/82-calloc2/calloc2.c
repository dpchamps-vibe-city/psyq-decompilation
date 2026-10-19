/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[82] CALLOC2.OBJ
 * sha256: 8f310bb94343fb4b420c062dfaa7b4891da35f0f94b0c16be63bd9b6b5024810
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: calloc2
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

void *malloc2(u32);
static void *func_000000BC(s8 *, s32);

void *calloc2(s32 arg0, s32 arg1) {
    s32 size;
    s8 *p;

    size = arg1 * arg0;
    p = malloc2(size);
    if (p == 0) {
        return 0;
    }
    func_000000BC(p, size);
    return p;
}
#include "common.h"

static void *func_000000BC(s8 *arg0, s32 arg1) {
    s8 *ret;

    ret = 0;
    if (arg0 != 0) {
        ret = arg0;
        if (arg1 == 0) {
            return 0;
        }
        do {
            *arg0 = 0;
            arg1 -= 1;
            arg0 += 1;
        } while (arg1 != 0);
    }
    return ret;
}
