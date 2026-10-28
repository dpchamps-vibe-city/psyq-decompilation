#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libpress.h>
#include <stdio.h>

extern s32 D_0000075C;
extern s32 D_0000079C;
extern s32 D_000007E0;

DECDCTENV *DecDCTGetEnv(DECDCTENV *env) {
    DECDCTENV *var_a2;
    s16 *var_a2_3;
    s32 *var_a1;
    s32 *var_a1_2;
    s32 *var_a1_3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u8 *var_a2_2;

    var_a2 = env;
    var_a1 = &D_0000075C;
    var_v1 = 0xF;
    do {
        temp_v0 = *var_a1;
        var_a1 += 1;
        var_v1 -= 1;
        (*(s32 *) ((u8 *) var_a2 + 0)) = temp_v0;
        var_a2 = (DECDCTENV *) ((u8 *) var_a2 + 4);
    } while (var_v1 != -1);
    var_a2_2 = env->iq_c;
    var_a1_2 = &D_0000079C;
    var_v1_2 = 0xF;
    do {
        temp_v0_2 = *var_a1_2;
        var_a1_2 += 1;
        var_v1_2 -= 1;
        (*(s32 *) ((u8 *) var_a2_2 + 0)) = temp_v0_2;
        var_a2_2 += 4;
    } while (var_v1_2 != -1);
    var_a2_3 = env->dct;
    var_a1_3 = &D_000007E0;
    var_v1_3 = 0x1F;
    do {
        temp_v0_3 = *var_a1_3;
        var_a1_3 += 1;
        var_v1_3 -= 1;
        (*(s32 *) ((u8 *) var_a2_3 + 0)) = temp_v0_3;
        var_a2_3 += 2;
    } while (var_v1_3 != -1);
    return env;
}
