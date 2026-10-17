#include "common.h"

u8 *bcopy(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *temp_v1;

    if (arg0 == 0) {
        return 0;
    }
    temp_v1 = arg0;
    if (arg2 > 0) {
        do {
            *arg1 = *arg0;
            arg0++;
            arg2--;
            arg1++;
        } while (arg2 > 0);
    }
    return temp_v1;
}
