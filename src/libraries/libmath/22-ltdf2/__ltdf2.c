#include "common.h"

typedef union {
    double value;
    struct {
        unsigned int lo;
        int hi;
    } words;
} DoubleBits;

int __ltdf2(double a, double b)
{
    DoubleBits x;
    DoubleBits y;
    int e1;
    int e2;
    int m1;
    int m2;
    int sign;
    int signMask;

    x.value = a;
    y.value = b;
    if (x.words.hi != y.words.hi || x.words.lo != y.words.lo) {
        if ((x.words.hi & 0x7FFFFFFF) || x.words.lo ||
            (y.words.hi & 0x7FFFFFFF) || y.words.lo) {
            signMask = 0x80000000;
            sign = x.words.hi & signMask;
            if (sign == (y.words.hi & signMask))
                goto compare;
            if (sign)
                return -1;
            return 0;

compare:
            e1 = (x.words.hi >> 20) & 0x7FF;
            e2 = (y.words.hi >> 20) & 0x7FF;
            if (e1 < e2)
                goto less;
            if (e1 != e2)
                goto greater;
            m1 = (x.words.hi & 0xFFFFF) | 0x100000;
            m2 = (y.words.hi & 0xFFFFF) | 0x100000;
            if (m1 < m2)
                goto less;
            if (m1 != m2)
                goto greater;
            if (x.words.lo >= y.words.lo)
                goto greater;

less:
            if (x.words.hi < 0)
                return 0;
            return -1;

greater:
            if (x.words.hi < 0)
                return -1;
            return 0;
        }
    }
    return 0;
}
