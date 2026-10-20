#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

DISPENV *SetDefDispEnv(DISPENV *env, int x, int y, int w, int h) {
    env->disp.x = (s16) x;
    env->disp.y = (s16) y;
    env->disp.w = (s16) w;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isrgb24 = 0;
    env->isinter = 0;
    env->pad1 = 0;
    env->pad0 = 0;
    env->disp.h = (s16) h;
    return env;
}
