#include "common.h"

extern volatile u32 *D_0000089C;
extern char RO_STR_00000708[];

static void func_00000684(char *msg);

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
