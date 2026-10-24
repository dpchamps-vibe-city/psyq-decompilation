#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void gte_rotate_x_matrix(MATRIX *arg0, s32 arg1) {
    s32 t;
    s32 c;
    s32 s;
    MATRIX m;

    t = arg1 / 360;
    c = rcos(t);
    s = rsin(t);
    if (arg1 != 0) {
        m.m[0][0] = 0x1000;
        m.m[0][1] = 0;
        m.m[0][2] = 0;
        m.m[1][0] = 0;
        m.m[1][1] = c;
        m.m[1][2] = -s;
        m.m[2][0] = 0;
        m.m[2][1] = s;
        m.m[2][2] = c;
        m.t[0] = 0;
        m.t[1] = 0;
        m.t[2] = 0;
        MulMatrix(arg0, &m);
    }
}
