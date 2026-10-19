/* P00.OBJ: GetTPage */
#include "common.h"

s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y) {
    return ((tp & 3) << 7) | ((abr & 3) << 5) | ((s32) (y & 0x100) >> 4) | ((s32) (x & 0x3FF) >> 6) | ((y & 0x200) * 4);
}
