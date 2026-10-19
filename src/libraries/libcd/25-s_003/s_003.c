/* Original TU: library-input/psyq/LIB/Libcd.lib[25] S_003.OBJ
 * sha256: 1f07740858d3619c49907fa12b3eaf93fa207d9fcea87ecd2129ef4da2550304
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: CdStatus
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern u8 CD_status;

u8 CdStatus(void) {
    return CD_status;
}
