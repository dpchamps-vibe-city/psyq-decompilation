#include "common.h"

s32 csqrt_1(s32 a)
{
    s32 r[8];
    s32 t[8];
    s32 i;
    s32 repeat;

    r[1] = a + 0x5D50AD;
    t[1] = a - 0x5D50AD;
    i = 1;
    repeat = 4;
    for (; i < 7; i++) {
        if (i != repeat) {
            if (t[i] >= 0) {
                r[i + 1] = r[i] - (t[i] >> i);
                t[i + 1] = t[i] - (r[i] >> i);
            } else {
                r[i + 1] = r[i] + (t[i] >> i);
                t[i + 1] = t[i] + (r[i] >> i);
            }
        } else {
            s32 old_r;
            if (t[4] >= 0) {
                s32 x, y;
                old_r = r[4];
                x = old_r - (t[4] >> 4);
                y = t[4] - (old_r >> 4);
                r[4] = x;
                t[4] = y;
                if (t[4] >= 0) {
                    r[5] = r[4] - (t[4] >> 4);
                    t[5] = t[4] - (r[4] >> 4);
                } else {
                    r[5] = r[4] + (t[4] >> 4);
                    t[5] = t[4] + (r[4] >> 4);
                }
            } else {
                s32 x, y;
                old_r = r[4];
                x = old_r + (t[4] >> 4);
                y = t[4] + (old_r >> 4);
                r[4] = x;
                t[4] = y;
                if (t[4] >= 0) {
                    r[5] = r[4] - (t[4] >> 4);
                    t[5] = t[4] - (r[4] >> 4);
                } else {
                    r[5] = r[4] + (t[4] >> 4);
                    t[5] = t[4] + (r[4] >> 4);
                }
            }
        }
    }
    return r[7];
}
