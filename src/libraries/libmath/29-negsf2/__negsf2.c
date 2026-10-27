#include "common.h"

s32 __negsf2(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 ^ 0x80000000;
}
