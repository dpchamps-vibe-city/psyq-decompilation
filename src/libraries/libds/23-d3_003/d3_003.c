/* Original TU: library-input/psyq/LIB/LIBDS.LIB[23] D3_003.OBJ
 * sha256: 7364fd563d03abf16d2a1c872110149e1a5e2c039b3e3039587ad364dc8f2148
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: DsGetSector2
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 CD_getsector2();                                /* extern */

s32 DsGetSector2(void) {
    return CD_getsector2() == 0;
}
