#include "common.h"
#include <sys/types.h>
#include <libgte.h>

int IsIdMatrix(MATRIX *m)
{
    s32 v[3][3];
    s32 i;
    s32 j;
    s32 sum;

    v[0][0] = m->m[0][0] - 0x1000;
    v[0][1] = m->m[0][1];
    v[0][2] = m->m[0][2];
    v[1][0] = m->m[1][0];
    v[1][1] = m->m[1][1] - 0x1000;
    v[1][2] = m->m[1][2];
    v[2][0] = m->m[2][0];
    v[2][1] = m->m[2][1];
    v[2][2] = m->m[2][2] - 0x1000;

    sum = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (v[i][j] < 0) {
                v[i][j] = -v[i][j];
            }
            sum += v[i][j];
        }
    }
    return sum < 0x14;
}
