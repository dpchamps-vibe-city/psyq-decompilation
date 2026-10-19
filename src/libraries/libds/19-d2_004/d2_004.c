/* Original TU: library-input/psyq/LIB/LIBDS.LIB[19] D2_004.OBJ
 * sha256: 9ed8e8fdff5a02ce4187af4bb3d1e6f6da98bc172770acae18c7726f22e2f71d
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: DsLastCom
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 DS_lastcom();                                   /* extern */

s32 DsLastCom(void) {
    return DS_lastcom() & 0xFF;
}
