/* P01.OBJ from LIBGPU.LIB, function GetClut */
#include "common.h"

u16 GetClut(int x, int y) {
    return ((y << 6) | ((x >> 4) & 0x3F)) & 0xFFFF;
}
