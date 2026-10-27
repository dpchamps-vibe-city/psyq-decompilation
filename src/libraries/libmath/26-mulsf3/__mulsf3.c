#include "common.h"

typedef union {
    float value;
    int bits;
} FloatBits;

extern int _err_math(int, int);

float __mulsf3(float a, float b)
{
    FloatBits x;
    FloatBits y;
    int e1;
    int e2;
    int e;
    int m;
    unsigned int sign;

    x.value = a;
    y.value = b;
    sign = (x.bits & 0x80000000) ^ (y.bits & 0x80000000);
    if (!(x.bits & 0x7FFFFFFF) || !(y.bits & 0x7FFFFFFF)) {
        x.bits = sign;
        return x.value;
    }
    e1 = (x.bits >> 23) & 0xFF;
    x.bits = (x.bits & 0x7FFFFF) | 0x800000;
    e2 = (y.bits >> 23) & 0xFF;
    y.bits = (y.bits & 0x7FFFFF) | 0x800000;
    m = (x.bits >> 8) * (y.bits >> 8);
    m += ((x.bits & 0xFF) * (y.bits >> 8)) >> 8;
    m += ((y.bits & 0xFF) * (x.bits >> 8)) >> 8;
    e = e1 + e2 - 0x7E;
    if (m & 0x80000000) {
        m += 0x80;
        m = (unsigned int)m >> 8;
    } else {
        m += 0x40;
        if (m & 0x80000000) {
            m = (unsigned int)m >> 8;
        } else {
            m = (unsigned int)m >> 7;
            e--;
        }
    }
    m &= 0xFF7FFFFF;
    if (e >= 0xFF) {
        _err_math(0x22, 0xC);
        x.bits = sign ? 0xFF800000 : 0x7F800000;
    } else {
        x.bits = sign | (e << 23) | m;
    }
    return x.value;
}
