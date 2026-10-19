/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[16] P04.OBJ
 * sha256: 00d904bc2e7f206be264f364705344f7770eda74e83f82639c43c871d59814f7
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: NextPrim
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 NextPrim(s32 *arg0) {
    return (*arg0 & 0xFFFFFF) | 0x80000000;
}
