#include "common.h"
#include "library/libmath_arc.h"

double sqrt(double x)
{
    double y = 0.0;
    double z;

    if (x > 0.0) {
        y = 1.0;
        if (x > 1.0)
            y = x;
        do {
            z = y;
            y = (x / z + z) * 0.5;
        } while (y < z);
        return z;
    }
    if (x < 0.0)
        _err_math(33, 6);
    return y;
}
