#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyF3(POLY_F3 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 4;
    p->code = 0x20;
}
