#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetLineG3(LINE_G3 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 7;
    p->code = 0x58;
    p->pad = 0x55555555;
    p->p2 = 0;
}
