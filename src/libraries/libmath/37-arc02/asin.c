#include "library/libmath_arc.h"

double asin(double x)
{
    double s;

    if (fabs(x) > 1.0) {
        _err_math(33, 2);
        return 0.0;
    }
    s = sqrt(1.0 - x * x);
    if (s != 0.0)
        return atan(x / s);
    else {
        if (x > 0.0)
            return 1.5707963267948966;
        return -1.5707963267948966;
    }
}
