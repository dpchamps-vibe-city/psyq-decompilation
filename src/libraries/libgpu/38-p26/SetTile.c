#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetTile(TILE *p) {
    (*(s8 *) ((u8 *) p + 3)) = 3;
    p->code = 0x60;
}
