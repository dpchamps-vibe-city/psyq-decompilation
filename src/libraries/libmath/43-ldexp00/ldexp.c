#include "common.h"

extern double __muldf3(double, double);

double ldexp(double x, int n)
{
    double pow = 2.0;

    if (n < 0) {
        pow = 0.5;
        n = -n;
    }
    while (n != 0) {
        if (n & 1)
            x *= pow;
        pow *= pow;
        n >>= 1;
    }
    return x;
}
