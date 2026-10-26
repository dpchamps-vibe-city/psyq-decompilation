#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <stdio.h>
#include <stdlib.h>
#include "libgte-ppmft.h"

static int func_00001B80(MATRIX *m, int row, int col)
{
    int tmp[2][2];
    int sign;
    int i, j;
    int r, c;

    if ((u32)row >= 3 || col < 0 || col >= 3) {
        printf(RO_STR_00001CD8);
        exit();
    }
    sign = -1;
    if (((row + col) & 1) == 0) sign = 1;
    i = 0;
    for (r = 0; i < 2; r++) {
        if (r == row) r++;
        j = 0;
        for (c = 0; j < 2; c++) {
            if (c == col) c++;
            tmp[i][j++] = m->m[r][c];
        }
        i++;
    }
    return sign * (tmp[0][0] * tmp[1][1] - tmp[0][1] * tmp[1][0]);
}
