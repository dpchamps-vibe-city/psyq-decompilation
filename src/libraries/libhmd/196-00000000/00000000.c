/* Original TU: library-input/psyq/LIB/LIBHMD.LIB[196] 00000000.OBJ
 * sha256: 0d7bfad8ed1de2902209047981456a1d7662de9e9511c6544d36e1c4aa2483a2
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: GsU_00000000
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

void *GsU_00000000(u16 **arg0) {
    u16 *temp_v1;

    temp_v1 = *arg0;
    return (void *) ((u8 *) temp_v1 + (*temp_v1 * 4));
}
