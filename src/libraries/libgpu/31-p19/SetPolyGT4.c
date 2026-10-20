#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyGT4(POLY_GT4 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 0xC;
    p->code = 0x3C;
}
