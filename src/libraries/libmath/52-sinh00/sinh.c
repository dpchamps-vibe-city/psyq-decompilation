#include "common.h"
#include <libmath.h>

extern int __ltdf2(double, double);
extern int __gtdf2(double, double);
extern double __negdf2(double);
extern double __adddf3(double, double);
extern double __subdf3(double, double);
extern double __muldf3(double, double);
extern double __divdf3(double, double);

double sinh(double x)
{
    double y;

    if (x < 0.0 ? -x > 0.001 : x > 0.001) {
        y = exp(x);
        return (y - 1.0 / y) * 0.5;
    }
    return x * (1.0 + x * x / 6.0);
}
