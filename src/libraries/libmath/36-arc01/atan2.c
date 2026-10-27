#include "common.h"
#include "library/libmath_arc.h"

#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846

double atan2(double y, double x)
{
    if (x == 0.0) {
        if (y == 0.0) {
            _err_math(0x21, 1);
            return 0.0;
        }
        if (y > 0.0)
            return M_PI_2;
        return -M_PI_2;
    }
    if ((y >= 0.0 || y < 0.0) && x >= 0.0)
        return asin(y / hypot(x, y));
    if (y >= 0.0 && x < 0.0)
        return M_PI - asin(y / hypot(x, y));
    if (y < 0.0 && x < 0.0)
        return -M_PI - asin(y / hypot(x, y));
}
