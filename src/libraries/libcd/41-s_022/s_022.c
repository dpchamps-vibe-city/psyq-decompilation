/* Original TU: library-input/psyq/LIB/Libcd.lib[41] S_022.OBJ
 * sha256: df61c15a24f9cd49c985f74852a5a6dd5a9e695a81538d0ef5cf1484fc9d0299
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: CdGetSector2
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 CD_getsector2();                                /* extern */

s32 CdGetSector2(void) {
    return CD_getsector2() == 0;
}
