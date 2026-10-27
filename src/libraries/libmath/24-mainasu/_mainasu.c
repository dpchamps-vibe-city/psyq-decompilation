#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

extern DblMant _add_mant_d(DblMant, DblMant);

DblMant _mainasu(DblMant a)
{
    DblMant one;

    one.hi = 0;
    one.lo = 1;
    a.hi = ~a.hi;
    a.lo = ~a.lo;
    a = _add_mant_d(a, one);
    return a;
}
