#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void gte_rotate_z_matrix(MATRIX *arg0, s32 arg1) {
    MATRIX mat;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v1;

    temp_s0 = arg1 / 360;
    temp_s0_2 = rcos(temp_s0);
    temp_v1 = rsin(temp_s0);
    if (arg1 != 0) {
        mat.m[0][0] = (s16) temp_s0_2;
        mat.m[0][1] = (s16) -temp_v1;
        mat.m[0][2] = 0;
        mat.m[1][0] = (s16) temp_v1;
        mat.m[1][1] = (s16) temp_s0_2;
        mat.m[1][2] = 0;
        mat.m[2][0] = 0;
        mat.m[2][1] = 0;
        mat.m[2][2] = ONE;
        mat.t[0] = 0;
        mat.t[1] = 0;
        mat.t[2] = 0;
        MulMatrix(arg0, &mat);
    }
}
