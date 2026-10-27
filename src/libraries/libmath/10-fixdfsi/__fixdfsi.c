#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

typedef union {
    double value;
    DblMant words;
} DoubleBits;

extern DblMant _dbl_shift(int, DblMant, int);
extern int _err_math(int, int);

int __fixdfsi(double x)
{
    DblMant m;
    DoubleBits v;
    int e;
    int n;
    int hi;
    int r;

    v.value = x;
    if (!(v.words.hi & 0x7FFFFFFF) && v.words.lo == 0)
        return 0;
    e = ((int)v.words.hi >> 20) & 0x7FF;
    n = e - 0x41D;
    if (n > 0) {
        _err_math(0x22, 0x11);
        r = 0x7FFFFFFF;
        if ((int)v.words.hi < 0)
            r = 0x80000000;
        return r;
    }
    m.hi = (v.words.hi & 0xFFFFF) | 0x100000;
    m.lo = v.words.lo;
    m = _dbl_shift(0, m, 10);
    hi = m.hi;
    if ((unsigned int)(e - 0x3FE) < 0x20 && hi != 0)
        hi = hi >> -n;
    else
        return 0;
    r = hi;
    if ((int)v.words.hi < 0)
        r = -r;
    return r;
}
