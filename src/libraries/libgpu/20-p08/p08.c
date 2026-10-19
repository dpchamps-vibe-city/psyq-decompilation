/* Original TU: library-input/psyq/LIB/LIBGPU.LIB[20] P08.OBJ
 * Functions: CatPrim
 */
#include "common.h"

void CatPrim(void *p0, void *p1) {
    *(u32 *)p0 = (*(u32 *)p0 & 0xFF000000) | ((u32)p1 & 0xFFFFFF);
}
