#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

static s32 func_000005EC(s32 arg0) {
    s32 count;

    count = 0;
    if (arg0 > 0) {
        do {
            arg0 >>= 1;
            count++;
        } while (arg0 > 0);
    }
    return count;
}
