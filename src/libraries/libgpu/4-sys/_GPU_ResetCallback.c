#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

void DMACallback(int, void *);
s32 func_00002430(void);

void _GPU_ResetCallback(void) {
    DMACallback(2, func_00002430);
}
