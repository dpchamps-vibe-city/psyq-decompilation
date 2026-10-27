#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

int _comp_mant(DblMant a, DblMant b)
{
    if (a.hi > b.hi) {
        return 1;
    }
    if (a.hi < b.hi) {
        return -1;
    }
    if (a.lo > b.lo) {
        return 1;
    }
    if (a.lo < b.lo) {
        return -1;
    }
    return 0;
}
