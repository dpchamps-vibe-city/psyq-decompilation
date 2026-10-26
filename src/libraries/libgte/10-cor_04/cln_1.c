#include "common.h"
#include "libgte-log.h"

int cln_1(int a)
{
    int x[8];
    int y[8];
    int i;
    int sum;
    int result;

    x[0] = a;
    y[0] = 0;
    for (i = 1; i < 7; i++) {
        sum = x[i - 1] + (x[i - 1] >> i);
        if (sum >= 4096) {
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        } else {
            x[i] = sum;
            y[i] = y[i - 1] - H_ln_tbl[i];
        }
    }
    result = y[6] - 4096;
    return result + x[6];
}
