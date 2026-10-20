#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetLineF4(LINE_F4 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 6;
    p->code = 0x4C;
    p->pad = 0x55555555;
}
