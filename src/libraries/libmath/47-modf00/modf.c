#include "common.h"
#include <libmath.h>

double modf(double x, double *iptr)
{
    union {
        double d;
        struct {
            u32 lo;
            s32 hi;
        } w;
    } u;
    s32 exp;
    s32 k;
    s32 sh;

    u.d = x;
    exp = (u.w.hi >> 20) & 0x7FF;
    if (exp - 0x41D < -0x1E) {
        *iptr = 0.0;
        return x;
    }
    k = exp - 0x413;
    if (k > 0) {
        if (k >= 32) {
            *iptr = x;
            return 0.0;
        } else {
            sh = 32 - k;
            u.w.lo >>= sh;
            u.w.lo <<= sh;
        }
    } else {
        sh = -k;
        u.w.hi >>= sh;
        u.w.hi <<= sh;
        u.w.lo = 0;
    }
    *iptr = u.d;
    return x - u.d;
}
