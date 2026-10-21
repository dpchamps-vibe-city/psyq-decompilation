#include "common.h"


extern void rescpy(u8 *dst, u8 *src);

static void func_00000FE4(u8 arg0, u8 *arg1) {
    u8 *p;
    s32 n;
    u8 status;

    if ((arg0 & 0xFF) != 5) {
        n = D_00001314[D_00001240.command] - 1;
        if (n < 0) {
            return;
        }
    } else {
        n = 0;
    }
    p = arg1 + n;
    status = *p;
    D_00001240.flags[0] = status >> 7;
    D_00001240.flags[1] = (status >> 6) & 1;
    D_00001240.flags[2] = (status >> 5) & 1;
    D_00001240.flags[3] = (status >> 1) & 1;
    D_00001240.status = status;
    rescpy(D_00001240.result, arg1);
}
