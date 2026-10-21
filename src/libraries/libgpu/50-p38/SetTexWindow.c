#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetTexWindow(DR_TWIN *p, RECT *tw) {
    (*(s8 *) ((u8 *) p + 3)) = 2;
    if (tw != 0) {
        p->code[0] = 0xE2000000 |
            (((u8) tw->y >> 3) << 15) |
            (((u8) tw->x >> 3) << 10) |
            ((-tw->h << 2) & 0x3E0) |
            ((-tw->w & 0xFF) >> 3);
    } else {
        p->code[0] = 0;
    }
    p->code[1] = 0;
}
