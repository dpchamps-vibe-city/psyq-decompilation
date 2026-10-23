#include "common.h"

long GsGetVcount(void) {
    volatile long v;
    long c;

    do {
        v = GetRCnt(0xF2000001U);
        c = v;
    } while (c != GetRCnt(0xF2000001U));
    return v;
}
