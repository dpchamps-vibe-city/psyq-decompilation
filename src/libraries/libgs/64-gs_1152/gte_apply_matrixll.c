#include "common.h"

void gte_apply_matrixll(s16 *arg0, s32 *arg1, s32 *arg2) {
    if ((*(s32 *) arg0 == 0x1000) && (arg0[2] == 0)) {
        arg2[0] = arg1[0];
    } else {
        arg2[0] = ((s32) arg0[0] * arg1[0] + (s32) arg0[1] * arg1[1] + (s32) arg0[2] * arg1[2]) >> 0xC;
    }
    if ((arg0[3] == 0) && (*(s32 *) &arg0[4] == 0x1000)) {
        arg2[1] = arg1[1];
    } else {
        arg2[1] = ((s32) arg0[3] * arg1[0] + (s32) arg0[4] * arg1[1] + (s32) arg0[5] * arg1[2]) >> 0xC;
    }
    if ((*(s32 *) &arg0[6] == 0) && (arg0[8] == 0x1000)) {
        arg2[2] = arg1[2];
    } else {
        arg2[2] = ((s32) arg0[6] * arg1[0] + (s32) arg0[7] * arg1[1] + (s32) arg0[8] * arg1[2]) >> 0xC;
    }
}
