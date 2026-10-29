#include "common.h"
#include "libpress_internal.h"

static s32 func_00000544(void) {
    volatile s32 timeout = 0x100000;

    while (*D_0000089C & 0x20000000) {
        timeout--;
        if (timeout == -1) {
            func_00000684(RO_STR_00000708 + 28);
            return -1;
        }
    }
    return 0;
}
