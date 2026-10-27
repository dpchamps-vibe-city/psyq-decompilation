#include "library/libmath_arc.h"

double acos(double x)
{
    if (fabs(x) > 1.0) {
        _err_math(33, 3);
        return 0.0;
    }
    return 1.5707963267948966 - asin(x);
}
