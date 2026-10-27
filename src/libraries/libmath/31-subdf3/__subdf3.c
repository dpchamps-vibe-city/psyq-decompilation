#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblBits;

typedef union {
    double value;
    DblBits words;
} DoubleBits;

extern double __negdf2(double);
extern double __adddf3(double, double);

double __subdf3(double a, double b)
{
    DoubleBits x;
    DoubleBits y;

    x.value = a;
    y.value = b;
    if (!(y.words.hi & 0x7FFFFFFF) && y.words.lo == 0)
        return x.value;
    if (!(x.words.hi & 0x7FFFFFFF) && x.words.lo == 0)
        return __negdf2(y.value);
    y.words.hi ^= 0x80000000;
    return __adddf3(a, y.value);
}
