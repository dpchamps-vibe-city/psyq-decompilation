#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

s32 func_00000238();                   /* static */

void GetDrawOffset(DR_OFFSET *p) {
    p->code[0] = func_00000238(5) | 0xE5000000;
}
