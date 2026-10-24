#include "common.h"

void gte_apply_matrixl(s16 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, s32 *arg6) {
    if ((*(s32 *) arg0 == 0x1000) && (arg0[2] == 0)) {
        *arg4 = arg1;
    } else {
        *arg4 = ((s32) arg0[0] * arg1 + (s32) arg0[1] * arg2 + (s32) arg0[2] * arg3) >> 0xC;
    }
    if ((arg0[3] == 0) && (*(s32 *) &arg0[4] == 0x1000)) {
        *arg5 = arg2;
    } else {
        *arg5 = ((s32) arg0[3] * arg1 + (s32) arg0[4] * arg2 + (s32) arg0[5] * arg3) >> 0xC;
    }
    if ((*(s32 *) &arg0[6] == 0) && (arg0[8] == 0x1000)) {
        *arg6 = arg3;
    } else {
        *arg6 = ((s32) arg0[6] * arg1 + (s32) arg0[7] * arg2 + (s32) arg0[8] * arg3) >> 0xC;
    }
}
