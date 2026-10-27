#include "common.h"
#include <libmath.h>

double atan(double x)
{
    double z;
    int i;
    int sign;

    if (x > 1.0) {
        sign = 1;
        x = 1.0 / x;
    } else if (x < -1.0) {
        sign = -1;
        x = 1.0 / x;
    } else {
        sign = 0;
    }

    for (z = 0.0, i = 19; i > 0; i--)
        z = (i * i * x * x) / (2 * i + 1 + z);

    if (sign > 0)
        return 1.57079632679489661923 - x / (1.0 + z);
    if (sign < 0)
        return -1.57079632679489661923 - x / (1.0 + z);
    return x / (1.0 + z);
}
