/* Original TU: library-input/psyq/LIB/LIBGS.LIB[25] GS_0021.OBJ
 * sha256: 8ae0025fc8d0a4b223bccd272dc5d30056f04362a633fefb06218d859a18670e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: GsGetActiveBuff
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern s16 PSDIDX;

s16 GsGetActiveBuff(void) {
    return PSDIDX;
}
