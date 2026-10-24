#include "common.h"

s32 gte_scale_matrix(s16 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 res = 0;
    if (arg1 != 0x1000) {
        res = 1;
        arg0[0] = (s16) (((s32) arg0[0] * arg1) >> 0xC);
        arg0[3] = (s16) (((s32) arg0[3] * arg1) >> 0xC);
        arg0[6] = (s16) (((s32) arg0[6] * arg1) >> 0xC);
    }
    if (arg2 != 0x1000) {
        res = 1;
        arg0[1] = (s16) (((s32) arg0[1] * arg2) >> 0xC);
        arg0[4] = (s16) (((s32) arg0[4] * arg2) >> 0xC);
        arg0[7] = (s16) (((s32) arg0[7] * arg2) >> 0xC);
    }
    if (arg3 != 0x1000) {
        res = 1;
        arg0[2] = (s16) (((s32) arg0[2] * arg3) >> 0xC);
        arg0[5] = (s16) (((s32) arg0[5] * arg3) >> 0xC);
        arg0[8] = (s16) (((s32) arg0[8] * arg3) >> 0xC);
    }
    return res;
}
