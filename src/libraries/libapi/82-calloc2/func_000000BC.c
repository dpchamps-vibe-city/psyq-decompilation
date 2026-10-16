#include "common.h"

static void *func_000000BC(s8 *arg0, s32 arg1) {
    s8 *ret;

    ret = 0;
    if (arg0 != 0) {
        ret = arg0;
        if (arg1 == 0) {
            return 0;
        }
        do {
            *arg0 = 0;
            arg1 -= 1;
            arg0 += 1;
        } while (arg1 != 0);
    }
    return ret;
}
