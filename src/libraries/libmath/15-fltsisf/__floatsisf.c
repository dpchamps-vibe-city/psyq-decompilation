#include "common.h"

typedef union {
    float value;
    unsigned int bits;
} FloatBits;

float __floatsisf(int x)
{
    unsigned int sign = 0;
    int e = 0x9D;
    FloatBits r;

    if (x == 0) {
        r.bits = 0;
        return r.value;
    }
    if (x == 0x80000000) {
        r.bits = 0xCF000000;
        return r.value;
    }
    if (x < 0) {
        sign = 0x80000000;
        x = -x;
    }
    while (x <= 0xFFFFFF) {
        x <<= 4;
        e -= 4;
    }
    while (x <= 0x3FFFFFFF) {
        x <<= 1;
        e -= 1;
    }
    x += 0x40;
    if (x < 0) {
        e += 1;
        x = (unsigned int)x >> 8;
    } else {
        x = (unsigned int)x >> 7;
    }
    e = sign | (e << 23);
    r.bits = e | (x & 0xFF7FFFFF);
    return r.value;
}
