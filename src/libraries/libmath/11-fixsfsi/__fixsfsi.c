#include "common.h"

typedef union {
    float value;
    unsigned int bits;
} FloatBits;

extern int _err_math(int, int);

int __fixsfsi(float f)
{
    FloatBits x;
    int e, n, m, r;

    x.value = f;
    if (!(x.bits & 0x7FFFFFFF))
        return 0;
    e = (((int)x.bits >> 23) & 0xFF);
    n = e - 0x9D;
    if (n > 0) {
        if (!(x.bits & 0x80000000)) {
            _err_math(0x22, 0x12);
            r = 0x7FFFFFFF;
        } else {
            r = 0x80000000;
        }
    } else {
        m = ((x.bits & 0x7FFFFF) | 0x800000) << 7;
        if ((unsigned int)(e - 0x7E) < 0x20 && m != 0)
            m = m >> -n;
        else
            return 0;
        r = m;
        if (x.bits & 0x80000000)
            r = -r;
    }
    return r;
}
