#include "common.h"

typedef union {
    float value;
    int bits;
} FloatBits;

extern int _err_math(int, int);

float __divsf3(float a, float b)
{
    FloatBits x;
    FloatBits y;
    int e1;
    int e2;
    int e;
    int q;
    int bit;
    int n;
    unsigned int sign;

    x.value = a;
    y.value = b;
    e1 = ((int)x.bits >> 23) & 0xFF;
    e2 = ((int)y.bits >> 23) & 0xFF;
    e = e1 - e2 + 0x7E;
    sign = (x.bits & 0x80000000) ^ (y.bits & 0x80000000);
    if (!(y.bits & 0x7FFFFFFF)) {
        x.value = sign ? 0xFFFFFFFF : 0x7FFFFFFF;
        return x.value;
    }
    if (!(x.bits & 0x7FFFFFFF)) {
        x.bits = sign;
        return x.value;
    }
    x.bits = (x.bits & 0x7FFFFF) | 0x800000;
    y.bits = (y.bits & 0x7FFFFF) | 0x800000;
    bit = 0x1000000;
    if (x.bits < y.bits) {
        x.bits <<= 1;
        e--;
    }
    q = 0;
    do {
        if (x.bits >= y.bits) {
            q |= bit;
            x.bits -= y.bits;
        }
        bit >>= 1;
        x.bits <<= 1;
    } while (bit);
    if (e >= 0) {
        q += 1;
        e++;
        q >>= 1;
    } else {
        n = -e;
        q += 1 << n;
        q >>= n + 1;
        e = 0;
    }
    q &= 0xFF7FFFFF;
    if (e >= 0xFF) {
        _err_math(0x22, 0xE);
        x.bits = sign ? 0xFF800000 : 0x7F800000;
    } else {
        x.bits = sign | (e << 23) | q;
    }
    return x.value;
}
