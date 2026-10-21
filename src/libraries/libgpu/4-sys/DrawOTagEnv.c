#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern char RO_STR_00003134[];

static void func_00001448(DR_ENV *arg0, DRAWENV *arg1);

void DrawOTagEnv(u_long *p, DRAWENV *env) {
    DR_ENV *temp_s0;

    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_00003134, p, env);
    }
    temp_s0 = &env->dr_env;
    func_00001448(temp_s0, env);
    env->dr_env.tag = (env->dr_env.tag & 0xFF000000) | ((u_long) p & 0xFFFFFF);
    ((void (*)(u32, DR_ENV *, int, int)) D_000031F0->unk8)(D_000031F0->unk18, temp_s0, 0x40, 0);
    ((void *(*)(void *, const void *, u32)) memcpy)((u8 *) &GEnv + 0x10, env, 0x5C);
}
