#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

u32 func_00001808();              /* static */

void SetDrawOffset(DR_OFFSET *p, u_short *ofs) {
    (*(s8 *) ((u8 *) p + 3)) = 2;
    p->code[0] = func_00001808((s16) ofs[0], (s16) ofs[1]);
    p->code[1] = 0;
}
