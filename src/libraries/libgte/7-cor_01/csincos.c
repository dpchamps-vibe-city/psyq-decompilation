#include "common.h"
#include "include_asm.h"

extern u32 H_cor_tbl[];

void csincos(s32 a, s32 *s, s32 *c) {
    s32 x[8];
    s32 y[8];
    s32 z[8];
    s32 i;

    x[0] = 0x9B7;
    y[0] = 0;
    z[0] = a;
    for (i = 0; i < 6; i++) {
        if (z[i] >= 0) {
            x[i + 1] = x[i] - (y[i] >> i);
            y[i + 1] = y[i] + (x[i] >> i);
            z[i + 1] = z[i] - H_cor_tbl[i];
        } else {
            x[i + 1] = x[i] + (y[i] >> i);
            y[i + 1] = y[i] - (x[i] >> i);
            z[i + 1] = z[i] + H_cor_tbl[i];
        }
    }
    *c = x[6] - ((z[6] * y[6]) >> 12);
    *s = y[6] + ((z[6] * x[6]) >> 12);
}
