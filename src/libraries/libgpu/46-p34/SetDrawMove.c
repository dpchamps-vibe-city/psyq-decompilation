#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetDrawMove(DR_MOVE *p, RECT *rect, int x, int y) {
    s8 var_a0;

    var_a0 = 5;
    if ((rect->w == 0) || (rect->h == 0)) {
        var_a0 = 0;
    }
    p->code[0] = 0x01000000;
    p->code[1] = 0x80000000;
    (*(s8 *) ((u8 *) p + 3)) = var_a0;
    p->code[2] = *(u32 *) ((u8 *) rect + 0);
    p->code[3] = (y << 0x10) | (x & 0xFFFF);
    p->code[4] = *(u32 *) ((u8 *) rect + 4);
}
