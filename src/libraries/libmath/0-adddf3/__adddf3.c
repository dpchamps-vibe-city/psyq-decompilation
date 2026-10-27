#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

typedef union {
    double value;
    DblMant words;
} DoubleBits;

extern DblMant _add_mant_d(DblMant, DblMant);
extern DblMant _mainasu(DblMant);
extern DblMant _dbl_shift(int, DblMant, int);
extern int _err_math(int, int);

double __adddf3(double a, double b)
{
    DblMant m1;
    DblMant m2;
    DblMant round;
    DoubleBits zero;
    DoubleBits x;
    DoubleBits y;
    int e1;
    int e2;
    unsigned int sign;

    zero.words.lo = 0;
    zero.words.hi = 0;
    sign = 0;
    x.value = a;
    y.value = b;
    if (!(x.words.hi & 0x7FFFFFFF) && x.words.lo == 0)
        return b;
    if (!(y.words.hi & 0x7FFFFFFF) && y.words.lo == 0)
        return x.value;
    e1 = ((int)x.words.hi >> 20) & 0x7FF;
    e2 = ((int)y.words.hi >> 20) & 0x7FF;
    if (e2 + 54 < e1)
        return x.value;
    if (e1 + 54 < e2)
        return y.value;
    m1.hi = (x.words.hi & 0xFFFFF) | 0x100000;
    m1.lo = x.words.lo;
    m2.hi = (y.words.hi & 0xFFFFF) | 0x100000;
    m2.lo = y.words.lo;
    if (x.words.hi & 0x80000000)
        m1 = _mainasu(m1);
    if (y.words.hi & 0x80000000)
        m2 = _mainasu(m2);
    m1 = _dbl_shift(0, m1, 9);
    m2 = _dbl_shift(0, m2, 9);
    if (e2 < e1) {
        m2 = _dbl_shift(1, m2, e1 - e2);
    } else {
        m1 = _dbl_shift(1, m1, e2 - e1);
        e1 = e2;
    }
    m1 = _add_mant_d(m1, m2);
    if ((int)m1.hi >= 0) {
        if (m1.hi == 0 && m1.lo == 0)
            return zero.value;
    } else {
        m1 = _mainasu(m1);
        sign = 0x80000000;
    }
    while (!(m1.hi & 0xE0000000)) {
        m1 = _dbl_shift(0, m1, 1);
        e1--;
    }
    if (m1.hi & 0x40000000) {
        m1 = _dbl_shift(1, m1, 1);
        e1++;
    }
    round.hi = 0;
    round.lo = (m1.lo & 0x200) ? 0x100 : 0xFF;
    m1 = _add_mant_d(m1, round);
    if (m1.hi & 0x40000000) {
        m1 = _dbl_shift(1, m1, 1);
        e1++;
    }
    m1 = _dbl_shift(1, m1, 9);
    m1.hi &= 0xFFEFFFFF;
    if (e1 >= 0x7FF) {
        _err_math(0x22, 0xB);
        x.words.hi = sign ? 0xFFF00000 : 0x7FF00000;
        x.words.lo = 0;
    } else {
        x.words.hi = sign | (e1 << 20) | m1.hi;
        x.words.lo = m1.lo;
    }
    return x.value;
}
