#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern int K_cor_tbl[];

int catan(int a)
{
    int x[14];
    int y[14];
    int z[14];
    int i;

    x[0] = 4096;
    y[0] = a;
    z[0] = 0;
    for (i = 0; i < 12; i++) {
        if (y[i] < 0) {
            x[i + 1] = x[i] - (y[i] >> i);
            y[i + 1] = y[i] + (x[i] >> i);
            z[i + 1] = z[i] - K_cor_tbl[i];
        } else {
            x[i + 1] = x[i] + (y[i] >> i);
            y[i + 1] = y[i] - (x[i] >> i);
            z[i + 1] = z[i] + K_cor_tbl[i];
        }
    }
    return z[12];
}
