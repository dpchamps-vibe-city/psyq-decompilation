#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern char RO_STR_00000290[];
extern char RO_STR_000002AC[];
extern char RO_STR_000002C8[];
extern char RO_STR_000002D4[];

void DumpDispEnv(DISPENV *env) {
    GPU_printf(RO_STR_00000290, env->disp.x, env->disp.y, env->disp.w, (s32) env->disp.h);
    GPU_printf(RO_STR_000002AC, env->screen.x, env->screen.y, env->screen.w, (s32) env->screen.h);
    GPU_printf(RO_STR_000002C8, env->isinter);
    GPU_printf(RO_STR_000002D4, env->isrgb24);
}
