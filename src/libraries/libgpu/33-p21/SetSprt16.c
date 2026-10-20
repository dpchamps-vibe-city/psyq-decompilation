#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetSprt16(SPRT_16 *p) {
    (*(s8 *) ((u8 *) p + 3)) = 3;
    p->code = 0x7C;
}
