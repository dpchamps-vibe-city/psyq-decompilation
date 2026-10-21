#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

DISPENV *GetDispEnv(DISPENV *env) {
    ((void *(*)(void *, const void *, u32)) memcpy)(env, (u8 *) &GEnv + 0x6C, 0x14);
    return env;
}
