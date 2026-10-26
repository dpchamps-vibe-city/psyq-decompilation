#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static long func_000005EC(long arg0) {
    long count;

    count = 0;
    if (arg0 > 0) {
        do {
            arg0 >>= 1;
            count++;
        } while (arg0 > 0);
    }
    return count;
}
