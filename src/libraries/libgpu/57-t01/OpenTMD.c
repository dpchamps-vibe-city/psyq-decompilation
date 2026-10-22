#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

static s32 func_00000360(u_long *arg0, s32 arg1, void **arg2, SVECTOR **arg3, SVECTOR **arg4);
extern SVECTOR *B_00001888;
extern SVECTOR *B_0000188C;
extern void *B_00001890;
extern s32 B_00001894;

int OpenTMD(u_long *tmd, int obj_no) {
    s32 temp_v0;

    temp_v0 = func_00000360(tmd, obj_no, &B_00001890, &B_00001888, &B_0000188C);
    B_00001894 = temp_v0;
    return temp_v0;
}
