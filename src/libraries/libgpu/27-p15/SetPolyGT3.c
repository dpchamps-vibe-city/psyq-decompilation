#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyGT3(POLY_GT3 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 9;
    p->code = 0x34;
}
