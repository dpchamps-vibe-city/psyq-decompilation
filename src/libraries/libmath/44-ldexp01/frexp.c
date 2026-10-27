#include "common.h"

typedef union {
    double d;
    int words[2];
} DoubleBits;

extern int __eqdf2(double, double);
extern double ldexp(double, int);

double frexp(double x, int *ep)
{
    DoubleBits u;
    int e;

    u.d = x;
    if (x == 0.0) {
        e = 0;
    } else {
        e = ((u.words[1] >> 20) & 0x7FF) - 0x3FE;
        u.d = ldexp(x, -e);
    }
    if (ep != 0)
        *ep = e;
    return u.d;
}
