#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

DRAWENV *GetDrawEnv(DRAWENV *env) {
    ((void *(*)(void *, const void *, u32)) memcpy)(env, (u8 *) &GEnv + 0x10, 0x5C);
    return env;
}
