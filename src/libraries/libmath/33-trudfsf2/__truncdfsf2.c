#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} Mant;

typedef union {
    float value;
    int bits;
} FloatBits;

typedef union {
    double value;
    Mant words;
} DoubleBits;

extern Mant _dbl_shift(int, Mant, int);
extern int _err_math(int, int);

float __truncdfsf2(double a)
{
    DoubleBits x;
    Mant m;
    Mant r;
    FloatBits z;
    int e;
    int n;
    int sf_exponent;
    unsigned int mant;

    x.value = a;
    if (!(x.words.hi & 0x7FFFFFFF) && !x.words.lo) {
        z.bits = x.words.hi & 0x80000000;
        return z.value;
    }
    sf_exponent = ((int)x.words.hi >> 20) & 0x7FF;
    e = sf_exponent - 0x380;
    m.hi = (x.words.hi & 0xFFFFF) | 0x100000;
    m.lo = x.words.lo;
    r = _dbl_shift(0, m, 4);
    mant = r.hi;
    if (e > 0) {
        mant += 1;
        mant >>= 1;
        if (mant & 0xFF000000) {
            mant >>= 1;
            e = sf_exponent - 0x37F;
        }
    } else {
        n = -e;
        mant += 1 << (n + 1);
        mant >>= n + 2;
        e = 0;
    }
    mant &= 0xFF7FFFFF;
    if (e >= 0xFF) {
        _err_math(0x22, 0x10);
        z.bits = ((int)x.words.hi < 0) ? 0xFF800000 : 0x7F800000;
    } else {
        z.bits = (x.words.hi & 0x80000000) | (e << 23) | mant;
    }
    return z.value;
}
