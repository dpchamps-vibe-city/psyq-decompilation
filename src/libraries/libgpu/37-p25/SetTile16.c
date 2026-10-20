#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetTile16(TILE_16 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 2;
    p->code = 0x78;
}
