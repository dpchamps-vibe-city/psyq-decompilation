#include "common.h"
#include <libmath.h>

double floor(double x)
{
    if (x < 0.0) {
        if (modf(-x, &x) != 0.0)
            x += 1.0;
        return -x;
    }
    modf(x, &x);
    return x;
}
