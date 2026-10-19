/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[13] P01.OBJ
 * sha256: 6de49066ba5daf92fedca7b90349fb56fcc357f496713eb62f318eb53c0c57f7
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: GetClut
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 GetClut(s32 arg0, s32 arg1) {
    return ((arg1 << 6) | ((arg0 >> 4) & 0x3F)) & 0xFFFF;
}
