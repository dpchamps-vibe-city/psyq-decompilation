#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetDrawStp(DR_STP *p, int pbw) {
    (*(s8 *) ((u8 *) p + 3)) = 2;
    p->code[0] = 0xE6000000 | (pbw ? 0x01 : 0);
    p->code[1] = 0;
}
