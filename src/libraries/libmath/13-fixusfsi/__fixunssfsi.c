#include "common.h"

typedef union {
    float value;
    unsigned int bits;
} FloatBits;

extern int _err_math(int, int);

unsigned int __fixunssfsi(float f)
{
    FloatBits x;
    int e;
    int n;
    unsigned int m;
    int r;

    x.value = f;
    if ((int)x.bits < 0)
        _err_math(0x21, 0x14);
    if (!(x.bits & 0x7FFFFFFF))
        return 0;
    e = ((int)x.bits >> 23) & 0xFF;
    n = e - 0x9E;
    if (n > 0) {
        _err_math(0x22, 0x14);
        r = 0xFFFFFFFF;
    } else {
        m = ((x.bits & 0x7FFFFF) | 0x800000) << 8;
        if ((unsigned int)(e - 0x7F) < 0x20 && m != 0)
            m = m >> -n;
        else
            return 0;
        r = m;
        if ((int)x.bits < 0)
            r = -r;
    }
    return r;
}
