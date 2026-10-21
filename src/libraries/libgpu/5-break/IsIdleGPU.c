#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern volatile s32 *D_000002A0;

int IsIdleGPU(int max_count) {
    int i;

    i = 0;
    while (!(*D_000002A0 & 0x04000000)) {
        if (i++ > max_count)
            return -1;
    }
    return 0;
}
