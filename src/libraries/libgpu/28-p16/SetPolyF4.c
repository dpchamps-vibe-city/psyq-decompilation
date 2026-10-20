#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyF4(POLY_F4 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 5;
    p->code = 0x28;
}
