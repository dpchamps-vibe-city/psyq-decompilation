#include "common.h"
#include <libmath.h>

static double func_00000070(double, int *);

double sin(double x)
{
    int quadrant;
    double y = func_00000070(x * 0.5, &quadrant);

    y = (y + y) / (y * y + 1.0);
    if (!(quadrant & 1))
        return y;
    return -y;
}
