#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetSprt(SPRT *p) {
    (*(s8 *) ((u8 *) p + 3)) = 4;
    p->code = 0x64;
}
