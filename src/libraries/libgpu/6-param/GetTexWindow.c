#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

s32 func_00000238();                   /* static */

void GetTexWindow(DR_TWIN *p) {
    p->code[0] = func_00000238(2) | 0xE2000000;
}
