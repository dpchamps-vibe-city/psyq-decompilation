#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetDrawMode(DR_MODE *p, int dfe, int dtd, int tpage, RECT *tw) {
    setlen(p, 2);
    p->code[0] = _get_mode(dfe, dtd, tpage);
    if (tw != 0) {
        p->code[1] = 0xE2000000 |
            (((u8) tw->y >> 3) << 15) |
            (((u8) tw->x >> 3) << 10) |
            ((-tw->h << 2) & 0x3E0) |
            ((-tw->w & 0xFF) >> 3);
        return;
    }
    p->code[1] = 0;
}
