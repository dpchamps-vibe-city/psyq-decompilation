#include "common.h"
#include <sys/types.h>
#include <libgte.h>

static int func_00001B80(MATRIX *, int, int);

static void func_00001AFC(MATRIX *m, int m2[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m2[i][j] = func_00001B80(m, j, i);
        }
    }
}
