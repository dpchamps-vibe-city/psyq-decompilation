#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>

DRAWENV *SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h) {
    s32 temp_v0;

    temp_v0 = GetVideoMode();
    env->clip.x = (s16) x;
    env->clip.y = (s16) y;
    env->clip.w = (s16) w;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    env->dtd = 1;
    env->clip.h = (s16) h;
    if (temp_v0 != 0) {
        env->dfe = h < 0x121;
    } else {
        env->dfe = h < 0x101;
    }
    env->ofs[0] = (s16) x;
    env->ofs[1] = (s16) y;
    env->tpage = 0xA;
    env->isbg = 0;
    return env;
}
