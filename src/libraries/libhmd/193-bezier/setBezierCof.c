#include "common.h"

void setBezierCof(int p0, int p1, int p2, int p3, short *out)
{
    int na = -p0;

    out[0] = na + 3 * (p1 - p2) + p3;
    out[1] = 3 * (p0 + p2) - 6 * p1;
    out[2] = 3 * (na + p1);
    out[3] = p0;
}
