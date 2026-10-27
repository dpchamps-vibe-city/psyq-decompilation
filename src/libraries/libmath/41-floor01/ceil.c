#include "common.h"
#include <libmath.h>

double ceil(double x)
{
    double ip;

    if (modf(x, &ip) == 0.0) {
        return floor(x);
    }
    return floor(x) + 1.0;
}
