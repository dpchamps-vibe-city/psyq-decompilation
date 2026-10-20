#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetLineG4(LINE_G4 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 9;
    p->code = 0x5C;
    p->pad = 0x55555555;
    p->p2 = 0;
    p->p3 = 0;
}
