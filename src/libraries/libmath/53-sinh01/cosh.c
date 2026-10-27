/* The function's double literals supply the complete original constant pool. */
#include "common.h"
#include <libmath.h>

extern double __adddf3(double, double);
extern double __muldf3(double, double);
extern double __divdf3(double, double);

double cosh(double x)
{
    double y;

    y = exp(x);
    return (y + 1.0 / y) * 0.5;
}
