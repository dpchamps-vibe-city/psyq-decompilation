#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetPriority(DR_STP *p, s32 arg1, s32 arg2) {
    u_long code;

    (*(s8 *) ((u8 *) p + 3)) = 2;
    code = 0xE6000000;
    if (arg1 != 0) {
        code = 0xE6000002;
    }
    p->code[0] = code | (arg2 != 0);
    p->code[1] = 0;
}
