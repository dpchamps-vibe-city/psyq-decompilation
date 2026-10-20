#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetLineF3(LINE_F3 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 5;
    p->code = 0x48;
    p->pad = 0x55555555;
}
