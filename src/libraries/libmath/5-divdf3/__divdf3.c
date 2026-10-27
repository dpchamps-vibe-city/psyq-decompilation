#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} Mant;

typedef union {
    double value;
    Mant words;
} DoubleBits;

extern Mant _add_mant_d(Mant, Mant);
extern Mant _mainasu(Mant);
extern Mant _dbl_shift(int, Mant, int);
extern Mant _dbl_shift_us(int, Mant, int);
extern int _comp_mant();
extern int _err_math(int, int);

double __divdf3(double a, double b)
{
    Mant q;
    Mant bit;
    Mant round;
    Mant m1;
    Mant m2;
    DoubleBits x;
    DoubleBits y;
    DoubleBits z;
    int e1;
    int e2;
    int e;
    int n;
    unsigned int sign;

    x.value = a;
    y.value = b;
    e1 = ((int)x.words.hi >> 20) & 0x7FF;
    e2 = ((int)y.words.hi >> 20) & 0x7FF;
    e = e1 - e2 + 0x3FE;
    sign = (x.words.hi & 0x80000000) ^ (y.words.hi & 0x80000000);
    if (!(y.words.hi & 0x7FFFFFFF)) {
        if (!y.words.lo) {
            z.words.hi = 0xFFFFFFFF;
            if (!sign)
                z.words.hi = 0x7FFFFFFF;
            z.words.lo = 0xFFFFFFFF;
            return z.value;
        }
    }
    if (!(x.words.hi & 0x7FFFFFFF)) {
        if (!x.words.lo) {
            z.words.hi = sign;
            z.words.lo = 0;
            return z.value;
        }
    }
    m1.hi = (x.words.hi & 0xFFFFF) | 0x100000;
    m1.lo = x.words.lo;
    m2.hi = (y.words.hi & 0xFFFFF) | 0x100000;
    m2.lo = y.words.lo;
    if (_comp_mant(m1, m2) < 0) {
        m1 = _dbl_shift(0, m1, 1);
        e--;
    }
    bit.hi = 0x200000;
    bit.lo = 0;
    q.lo = 0;
    q.hi = 0;
    do {
        if (_comp_mant(m1, m2) >= 0) {
            q.hi |= bit.hi;
            q.lo |= bit.lo;
            m1 = _add_mant_d(m1, _mainasu(m2));
        }
        m1 = _dbl_shift(0, m1, 1);
        bit = _dbl_shift_us(1, bit, 1);
    } while (bit.hi || bit.lo);
    if (e >= 0) {
        round.hi = 0;
        round.lo = 1;
        q = _add_mant_d(q, round);
        e++;
        q = _dbl_shift_us(1, q, 1);
    } else {
        n = -e;
        round.hi = 0;
        round.lo = 1 << n;
        q = _add_mant_d(q, round);
        e = 0;
        q = _dbl_shift_us(1, q, n + 1);
    }
    q.hi &= 0xFFEFFFFF;
    if (e >= 0x7FF) {
        _err_math(0x22, 0xF);
        z.words.hi = sign ? 0xFFF00000 : 0x7FF00000;
        z.words.lo = 0;
    } else {
        z.words.hi = sign | (e << 20) | q.hi;
        z.words.lo = q.lo;
    }
    return z.value;
}
