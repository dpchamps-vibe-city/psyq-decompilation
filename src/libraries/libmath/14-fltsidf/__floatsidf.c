#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

typedef union {
    double value;
    DblMant words;
} DoubleBits;

extern DblMant _dbl_shift_us(int, DblMant, int);

double __floatsidf(int x)
{
    DblMant m;
    DoubleBits r;
    unsigned int sign = 0;
    int e = 0x41D;

    if (x == 0) {
        r.words.lo = 0;
        r.words.hi = 0;
    } else if (x == 0x80000000) {
        r.words.hi = 0xC1E00000;
        r.words.lo = 0;
    } else {
        if (x < 0) {
            sign = 0x80000000;
            x = -x;
        }
        while (x <= 0xFFFFFF) {
            x <<= 4;
            e -= 4;
        }
        while (x <= 0x3FFFFFFF) {
            x <<= 1;
            e -= 1;
        }
        m.hi = x;
        m.lo = 0;
        m = _dbl_shift_us(1, m, 10);
        m.hi &= 0xFFEFFFFF;
        r.words.hi = m.hi | sign;
        r.words.hi |= e << 20;
        r.words.lo = m.lo;
    }
    return r.value;
}
