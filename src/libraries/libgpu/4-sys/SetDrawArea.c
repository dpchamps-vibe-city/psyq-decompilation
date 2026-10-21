#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

u32 func_000016D8();              /* static */
u32 func_00001770(s16 arg0, s16 arg1);              /* static */

void SetDrawArea(DR_AREA *p, RECT *r) {
    (*(s8 *) ((u8 *) p + 3)) = 2;
    p->code[0] = func_000016D8(r->x, r->y);
    p->code[1] = func_00001770((s16) (((u16) r->x + (u16) r->w) - 1), (s16) (((u16) r->y + (u16) r->h) - 1));
}
