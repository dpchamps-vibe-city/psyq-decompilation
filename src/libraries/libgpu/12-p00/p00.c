/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[12] P00.OBJ
 * sha256: 373f71c57a5ce556451669751162bf447c760fd3463343d4d80e565b8283f3b7
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: GetTPage
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

s32 GetTPage(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return ((arg0 & 3) << 7) | ((arg1 & 3) << 5) | ((s32) (arg3 & 0x100) >> 4) | ((s32) (arg2 & 0x3FF) >> 6) | ((arg3 & 0x200) * 4);
}
