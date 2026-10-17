#include "common.h"

void *bzero(void *arg0, s32 arg1) {
    void *var_v0;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 <= 0) {
        return 0;
    }
    var_v0 = arg0;
    do {
        *(s8 *)arg0 = 0;
        arg0 += 1;
        arg1 -= 1;
    } while (arg1 > 0);
    return var_v0;
}
