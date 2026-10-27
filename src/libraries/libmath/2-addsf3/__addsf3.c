#include "common.h"

typedef union {
    float value;
    unsigned int bits;
} FloatBits;

extern int _err_math(int, int);

float __addsf3(float a, float b)
{
    FloatBits zero;
    FloatBits x;
    FloatBits y;
    int m1;
    int m2;
    unsigned int e1;
    unsigned int e2;
    unsigned int sign;

    zero.bits = 0;
    sign = 0;
    x.value = a;
    y.value = b;
    if (!(x.bits & 0x7FFFFFFF))
        return b;
    if (!(y.bits & 0x7FFFFFFF))
        return x.value;
    e1 = ((int)x.bits >> 23) & 0xFF;
    e2 = ((int)y.bits >> 23) & 0xFF;
    if (e2 + 0x19 < e1)
        return x.value;
    if (e1 + 0x19 < e2)
        return y.value;
    m1 = ((x.bits & 0x7FFFFF) | 0x800000) << 6;
    m2 = ((y.bits & 0x7FFFFF) | 0x800000) << 6;
    if (x.bits & 0x80000000)
        m1 = -m1;
    if (y.bits & 0x80000000)
        m2 = -m2;
    if (e2 < e1) {
        m2 = m2 >> (e1 - e2);
    } else {
        m1 = m1 >> (e2 - e1);
        e1 = e2;
    }
    m1 = m1 + m2;
    if (m1 >= 0) {
        if (m1 == 0)
            return zero.value;
    } else {
        m1 = -m1;
        sign = 0x80000000;
    }
    while (!(m1 & 0xE0000000)) {
        m1 *= 2;
        e1--;
    }
    if (m1 & 0x40000000) {
        m1 = m1 >> 1;
        e1++;
    }
    m1 += (m1 & 0x40) ? 0x20 : 0x1F;
    if (m1 & 0x40000000) {
        m1 = m1 >> 1;
        e1++;
    }
    m1 = m1 >> 6;
    m1 &= 0xFF7FFFFF;
    if (e1 >= 0xFF) {
        _err_math(0x22, 0xA);
        x.bits = sign ? 0xFF800000 : 0x7F800000;
    } else {
        x.bits = sign | (e1 << 23) | m1;
    }
    return x.value;
}
