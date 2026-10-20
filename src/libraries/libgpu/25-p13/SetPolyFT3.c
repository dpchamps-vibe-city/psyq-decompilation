#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyFT3(POLY_FT3 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 7;
    p->code = 0x24;
}
