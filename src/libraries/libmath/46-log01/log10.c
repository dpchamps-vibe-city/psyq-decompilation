#include "common.h"

extern double log(double);
extern int __nedf2(double, double);
extern double __divdf3(double, double);

double log10(double x)
{
    if (log(x) != 0.0)
        return log(x) / 2.302585092994046;
    return 0.0;
}
