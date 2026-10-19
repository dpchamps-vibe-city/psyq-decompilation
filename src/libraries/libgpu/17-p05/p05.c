/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[17] P05.OBJ
 * sha256: 631822584d7c26f8087894a817cea641c5eda4f8aedcb9f657161db6619b9783
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: IsEndPrim
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 IsEndPrim(s32 *arg0) {
    return (*arg0 & 0xFFFFFF) == 0xFFFFFF;
}
