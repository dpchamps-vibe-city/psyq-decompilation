#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

void DrawPrim(void *p) {
    u8 temp_s1;

    temp_s1 = *(u8 *) ((u8 *) p + 3);
    (*(void (**)(int)) ((u8 *) D_000031F0 + 0x3C))(0);
    (*(void (**)(void *, u8)) ((u8 *) D_000031F0 + 0x14))((u8 *) p + 4, temp_s1);
}
