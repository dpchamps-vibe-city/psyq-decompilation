#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdio.h>

s32 func_000000EC();      /* static */

TIM_IMAGE *ReadTIM(TIM_IMAGE *timimg) {
    s32 temp_v0;

    temp_v0 = func_000000EC(B_00000238, timimg);
    if (temp_v0 == -1) {
        return 0;
    }
    B_00000238 = &B_00000238[temp_v0];
    return timimg;
}
