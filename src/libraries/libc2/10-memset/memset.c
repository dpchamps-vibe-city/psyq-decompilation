/* Original TU: library-input/psyq/LIB/LIBC2.LIB[10] MEMSET.OBJ
 * sha256: a27db6e485b21e296987474246289b9bf76b3dd125fe44b183b40535a1c1192b
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: memset
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

void *memset(void *arg0, int arg1, unsigned int arg2) {
    void *var_v0;

    if (arg0 == 0) {
        return 0;
    }
    if ((s32)arg2 <= 0) {
        return 0;
    }
    var_v0 = arg0;
    do {
        *(s8 *)arg0 = arg1;
        arg0 += 1;
        arg2 -= 1;
    } while ((s32)arg2 > 0);
    return var_v0;
}
