#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetLineF2(LINE_F2 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 3;
    p->code = 0x40;
}
