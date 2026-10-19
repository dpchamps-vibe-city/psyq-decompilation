/* Original TU: library-input/psyq/LIB/Libcd.lib[40] S_021.OBJ
 * sha256: c3543745ce4577539c3d8dbaea925eebefc27d62e2210d68a2bede93c93eca37
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: CdGetSector
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 CD_getsector();                                 /* extern */

s32 CdGetSector(void) {
    return CD_getsector() == 0;
}
