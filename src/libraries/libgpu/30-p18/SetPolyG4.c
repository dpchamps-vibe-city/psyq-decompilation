#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPolyG4(POLY_G4 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 8;
    p->code = 0x38;
}
