#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

s32 func_00000238();                   /* static */

void GetDrawArea(DR_AREA *p) {
    p->code[0] = func_00000238(3) | 0xE3000000;
    p->code[1] = func_00000238(4) | 0xE4000000;
}
