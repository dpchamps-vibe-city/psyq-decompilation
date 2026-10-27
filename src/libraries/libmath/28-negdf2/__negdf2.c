#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblBits;

typedef union {
    double value;
    unsigned long long ll;
    DblBits words;
} DoubleBits;

double __negdf2(double arg)
{
    DoubleBits u;

    u.value = arg;
    if (u.words.hi != 0 || u.words.lo != 0) {
        u.words.hi ^= 0x80000000;
        arg = u.value;
    }
    return arg;
}
