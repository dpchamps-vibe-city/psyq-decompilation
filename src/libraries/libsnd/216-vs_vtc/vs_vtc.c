/* Original TU: library-input/psyq/LIB/LIBSND.LIB[216] VS_VTC.OBJ
 * sha256: 36a7ef6ed3757cbfc7747714a8b2ab1470717bdb8be09239e5c1046297fb7fa4
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: SsVabTransCompleted
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s16 SpuIsTransferCompleted(s16);                    /* extern */

s16 SsVabTransCompleted(s16 arg0) {
    return SpuIsTransferCompleted(arg0);
}
