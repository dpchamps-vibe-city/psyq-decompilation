#include "common.h"

typedef union {
    double value;
    struct {
        unsigned int lo;
        int hi;
    } words;
} DoubleBits;

int __gtdf2(double a, double b)
{
    DoubleBits x;
    DoubleBits y;
    int e1;
    int e2;
    int m1;
    int m2;
    int sign;
    int signMask;
    int hi2;

    x.value = a;
    y.value = b;
    if (x.words.hi != y.words.hi || x.words.lo != y.words.lo) {
    if (!(x.words.hi & 0x7FFFFFFF) && x.words.lo == 0 &&
        !(y.words.hi & 0x7FFFFFFF)) {
        signMask = 0x80000000;
        sign = x.words.hi & signMask;
        if (y.words.lo == 0)
            return 0;
        goto signs_done;
    }
    signMask = 0x80000000;
    sign = x.words.hi & signMask;
signs_done:
    hi2 = y.words.hi;
    if (sign == (hi2 & signMask))
        goto compare;
    if (sign == 0)
        return 1;
    return 0;

compare:
    e1 = (x.words.hi >> 20) & 0x7FF;
    e2 = (y.words.hi >> 20) & 0x7FF;
    if (e2 < e1)
        goto greater;
    if (e1 != e2)
        goto less;
    m1 = (x.words.hi & 0xFFFFF) | 0x100000;
    m2 = (y.words.hi & 0xFFFFF) | 0x100000;
    if (m2 < m1)
        goto greater;
    if (m1 != m2)
        goto less;
    if (y.words.lo >= x.words.lo)
        goto less;

greater:
    if ((x.words.hi & 0x80000000) == 0)
        return 1;
    return 0;
less:
    if ((unsigned int)x.words.hi >= 0x80000000)
        return 1;
    return 0;
    }
    return 0;
}
