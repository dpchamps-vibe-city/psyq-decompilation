#include "common.h"
#include <libmath.h>

extern int _err_math(int, int);

double log(double x)
{
    double square, sum, previous;
    int exponent, i;

    if (x < 0.0) {
        _err_math(33, 4);
        return 0.0;
    }
    if (x == 0.0) {
        _err_math(34, 4);
        return 0.0;
    }
    frexp(x / 1.4142135623730951, &exponent);
    x /= ldexp(1.0, exponent);
    x = (x - 1.0) / (x + 1.0);
    square = x * x;
    sum = x;
    i = 1;
    do {
        previous = sum;
        x *= square;
        i += 2;
        sum += x / i;
    } while (previous != sum);
    return exponent * 0.6931471805599453 + (sum + sum);
}
