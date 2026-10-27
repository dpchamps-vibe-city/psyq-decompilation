#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

extern DblMant _add_mant_d(DblMant, DblMant);

DblMant _mul_mant_d(unsigned int a, unsigned int b)
{
    DblMant result;
    DblMant part;
    unsigned int a_lo;
    unsigned int p;

    a_lo = a & 0xFFFF;
    result.lo = a_lo * (b & 0xFFFF);
    result.hi = 0;
    a >>= 16;
    p = a * (b & 0xFFFF);
    part.hi = p >> 16;
    part.lo = p << 16;
    result = _add_mant_d(result, part);
    b >>= 16;
    p = a_lo * b;
    part.hi = p >> 16;
    part.lo = p << 16;
    result = _add_mant_d(result, part);
    result.hi += a * b;
    return result;
}
