#include "common.h"

void *memset(void *arg0, int arg1, unsigned int arg2) {
    void *var_v0;

    if (arg0 == 0) {
        return 0;
    }
    if ((s32)arg2 <= 0) {
        return 0;
    }
    var_v0 = arg0;
    do {
        *(s8 *)arg0 = arg1;
        arg0 += 1;
        arg2 -= 1;
    } while ((s32)arg2 > 0);
    return var_v0;
}
