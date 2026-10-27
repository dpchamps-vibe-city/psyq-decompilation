#include "common.h"
#include <libmath.h>

/* Original constants read by the retained range-reduction helper. */
static const double RO_000003D0[6] = {
    1.5707963267948966, 0.5, -0.5,
    1.57080078125, 4.454455103380769e-06, 1.0
};

static double func_00000070(double, int *);

double tan(double x)
{
    int quadrant;
    double result = func_00000070(x, &quadrant);

    if (!(quadrant & 1))
        return result;
    if (result != 0.0)
        return -1.0 / result;
    return 1.0e1000;
}
