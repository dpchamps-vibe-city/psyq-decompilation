/* P04.OBJ from LIBGPU.LIB: NextPrim */
#include "common.h"

s32 NextPrim(s32 *p) {
    return (*p & 0xFFFFFF) | 0x80000000;
}
