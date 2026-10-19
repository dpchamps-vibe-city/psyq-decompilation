/* P05.OBJ from LIBGPU.LIB: IsEndPrim */
#include "common.h"

s32 IsEndPrim(s32 *p) {
    return (*p & 0xFFFFFF) == 0xFFFFFF;
}
