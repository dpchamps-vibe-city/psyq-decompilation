#include "common.h"

int strcmp(const char *arg0, const char *arg1) {
    u8 c;
    if ((arg0 == 0) || (arg1 == 0)) {
        if (arg0 == arg1) {
            return 0;
        }
        if (arg0 == 0) {
            return -1;
        }
        return 1;
    }
    goto body;
exit_loop:
    return 0;
test:
    if (c == 0) {
        goto exit_loop;
    }
    arg0++;
body:
    c = *arg0;
    if (*(const s8 *)arg0 != *(const s8 *)arg1++) {
        arg0++;
        return *(const s8 *)(arg0 - 1) - *(const s8 *)(arg1 - 1);
    }
    goto test;
}
