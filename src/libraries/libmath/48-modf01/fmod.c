#include "common.h"
#include <libmath.h>

double fmod(double x, double y)
{
    double ip;

    if (y == 0.0)
        return 0.0;
    modf(x / y, &ip);
    return x - ip * y;
}
