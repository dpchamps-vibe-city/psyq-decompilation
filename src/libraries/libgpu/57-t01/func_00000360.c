#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_00001778[];
extern char RO_STR_0000178C[];
extern char RO_STR_000017B4[];
extern char RO_STR_000017CC[];
extern char RO_STR_000017E4[];

static s32 func_00000360(u_long *arg0, s32 arg1, void **arg2, SVECTOR **arg3, SVECTOR **arg4) {
    u_long *temp_s2;
    u_long *temp_v1;
    u_long *temp_v0;
    u_long *temp_v0_2;
    u_long *temp_v0_3;

    temp_s2 = arg0 + 3;
    if (GetGraphDebug() == 2) {
        printf(RO_STR_00001778);
    }
    if (GetGraphDebug() == 2) {
        printf(RO_STR_0000178C, arg0[0], arg0[1], arg0[2], arg1);
    }
    if (GetGraphDebug() == 2) {
        temp_v0 = (u_long *) ((arg1 * 0x1C) + (u_long) temp_s2);
        printf(RO_STR_000017B4, temp_v0[0], temp_v0[1]);
    }
    if (GetGraphDebug() == 2) {
        temp_v0_2 = (u_long *) ((arg1 * 0x1C) + (u_long) temp_s2);
        printf(RO_STR_000017CC, temp_v0_2[2], temp_v0_2[3]);
    }
    if (GetGraphDebug() == 2) {
        temp_v0_3 = (u_long *) ((arg1 * 0x1C) + (u_long) temp_s2);
        printf(RO_STR_000017E4, temp_v0_3[4], temp_v0_3[5]);
    }
    temp_v1 = (u_long *) ((((arg1 * 8) - arg1) * 4) + (u_long) temp_s2);
    *arg3 = (SVECTOR *) ((u8 *) temp_s2 + temp_v1[0]);
    *arg4 = (SVECTOR *) ((u8 *) temp_s2 + temp_v1[2]);
    *arg2 = (void *) ((u8 *) temp_s2 + temp_v1[4]);
    return temp_v1[5];
}
