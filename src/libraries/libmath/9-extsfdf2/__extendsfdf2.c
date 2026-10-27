#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} Mant;

typedef union {
    float value;
    unsigned int word;
} FloatBits;

typedef union {
    double value;
    Mant words;
} DoubleBits;

extern Mant _dbl_shift(int, Mant, int);

double __extendsfdf2(float a)
{
    FloatBits x;
    DoubleBits z;
    Mant m;
    Mant spare;
    int e;
    int sf_exponent;

    x.value = a;
    if (!(x.word & 0x7FFFFFFF)) {
        z.words.hi = x.word & 0x80000000;
        z.words.lo = 0;
        return z.value;
    } else {
        m.hi = x.word & 0x7FFFFF;
        m.lo = 0;
        sf_exponent = ((int)x.word >> 23) & 0xFF;
        if (sf_exponent) {
            e = sf_exponent + 0x380;
            m = _dbl_shift(1, m, 3);
        } else {
            e = 0x37E;
            while (m.hi & 0xFFE00000) {
                m = _dbl_shift(1, m, 1);
                e++;
            }
            while (!(m.hi & 0x100000)) {
                m.hi <<= 1;
                e--;
            }
            m.hi &= 0xFFEFFFFF;
        }
        z.words.hi = (x.word & 0x80000000) | (e << 20) | m.hi;
        z.words.lo = m.lo;
    }
    return z.value;
}
