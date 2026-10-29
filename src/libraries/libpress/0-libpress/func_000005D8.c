#include "common.h"

extern volatile u_long *D_0000087C;
extern char RO_STR_00000708[];

static void func_00000684(char *msg);

static s32 func_000005D8(void) {
    volatile s32 timeout = 0x100000;

    while (*D_0000087C & 0x1000000) {
        timeout--;
        if (timeout == -1) {
            func_00000684(RO_STR_00000708 + 44);
            return -1;
        }
    }
    return 0;
}
