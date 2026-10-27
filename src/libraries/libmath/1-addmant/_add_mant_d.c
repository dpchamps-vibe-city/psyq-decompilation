#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

DblMant _add_mant_d(DblMant a, DblMant b)
{
    DblMant x;
    DblMant y;

    x.hi = a.lo >> 16;
    x.lo = a.lo & 0xFFFF;
    y.hi = b.lo >> 16;
    y.lo = b.lo & 0xFFFF;
    x.lo = x.lo + y.lo;
    if (x.lo & 0x10000) {
        x.hi++;
    }
    x.hi = x.hi + y.hi;
    if (x.hi & 0x10000) {
        a.hi++;
    }
    a.lo = (x.hi << 16) | (x.lo & 0xFFFF);
    a.hi = a.hi + b.hi;
    return a;
}
