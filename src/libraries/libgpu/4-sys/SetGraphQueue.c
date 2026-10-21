#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

void DMACallback(int, void *);
extern char RO_STR_00003020[];


int SetGraphQueue(int arg0) {
    u8 temp_s2;

    temp_s2 = *(u8 *) ((u8 *) &GEnv + 1);
    if ((u8) (*(u8 *) ((u8 *) &(&GEnv)[1] + 1)) >= 2U) {
        GPU_printf(RO_STR_00003020, arg0);
    }
    if (arg0 != (*(u8 *) ((u8 *) &GEnv + 1))) {
        D_000031F0->unk34(1);
        (*(u8 *) ((u8 *) &GEnv + 1)) = arg0;
        DMACallback(2, 0);
    }
    return temp_s2;
}
