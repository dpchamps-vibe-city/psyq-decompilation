#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyFT4(POLY_FT4 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 9;
    p->code = 0x2C;
}
