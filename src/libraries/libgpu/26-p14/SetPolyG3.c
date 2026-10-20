#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyG3(POLY_G3 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 6;
    p->code = 0x30;
}
