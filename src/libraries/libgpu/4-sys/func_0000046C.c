#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern char RO_STR_00003078[];
extern char RO_STR_00003084[];
extern char RO_STR_00003098[];

static void func_0000046C(char *arg0, RECT *arg1) {
    switch (((u8 *) &GEnv)[2]) {
    case 1:
        if (arg1->w > *(s16 *) ((u8 *) &GEnv + 4) ||
            arg1->w + arg1->x > *(s16 *) ((u8 *) &GEnv + 4) ||
            arg1->y > *(s16 *) ((u8 *) &GEnv + 6) ||
            arg1->y + arg1->h > *(s16 *) ((u8 *) &GEnv + 6) ||
            arg1->w <= 0 || arg1->x < 0 || arg1->y < 0 || arg1->h <= 0) {
            GPU_printf(RO_STR_00003078, arg0);
            GPU_printf(RO_STR_00003084, arg1->x, arg1->y, arg1->w, arg1->h);
        }
        break;
    case 2:
        GPU_printf(RO_STR_00003098, arg0);
        GPU_printf(RO_STR_00003084, arg1->x, arg1->y, arg1->w, arg1->h);
        break;
    }
}
