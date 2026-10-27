#include "common.h"

s32 __nedf2(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v;

    if (((arg1 == arg3) && (arg0 == arg2)) ||
        (((arg1 & 0x7FFFFFFF) == 0) && (arg0 == 0) && ((arg3 & 0x7FFFFFFF) == 0) && (arg2 == 0))) {
        v = 0;
    } else {
        v = 1;
    }
    return v;
}
