#include "common.h"

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblMant;

DblMant _dbl_shift_us(int dir, DblMant m, int n)
{
    int i;

    if (dir == 0) {
        for (i = 0; i < n; i++) {
            m.hi <<= 1;
            if (m.lo & 0x80000000)
                m.hi |= 1;
            m.lo <<= 1;
        }
    } else {
        for (i = 0; i < n; i++) {
            m.lo >>= 1;
            if (m.hi & 1)
                m.lo |= 0x80000000;
            m.hi >>= 1;
        }
    }
    return m;
}
