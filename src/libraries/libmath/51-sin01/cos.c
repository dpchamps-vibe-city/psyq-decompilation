#include "common.h"
#include <libmath.h>

extern int __ltdf2(double, double);
extern double __adddf3(double, double);
extern double __subdf3(double, double);

double cos(double x)
{
    if (!(x < 0.0))
        return sin(1.5707963267948966 - x);
    return sin(x + 1.5707963267948966);
}
