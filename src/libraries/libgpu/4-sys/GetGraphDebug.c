#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

int GetGraphDebug(void) {
    return (s32) (*(u8 *) ((u8 *) &GEnv + 2));
}
