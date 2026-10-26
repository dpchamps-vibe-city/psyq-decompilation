#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdio.h>
#include <stdlib.h>

static void func_00001310(VECTOR *arg0, VECTOR *arg1, VECTOR *arg2, s32 arg3) {
    arg2->vx = (arg0->vx * (arg1->vz - arg3) + arg1->vx * (arg3 - arg0->vz)) / (arg1->vz - arg0->vz);
    arg2->vy = (arg0->vy * (arg1->vz - arg3) + arg1->vy * (arg3 - arg0->vz)) / (arg1->vz - arg0->vz);
    arg2->vz = arg3;
}
