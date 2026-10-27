#include "common.h"

typedef union {
    float value;
    unsigned int bits;
} FloatBits;

extern float __addsf3(float, float);
extern float __negsf2(float);

float __subsf3(float a, float b)
{
    FloatBits x;
    FloatBits y;

    x.value = a;
    y.value = b;
    if (!(y.bits & 0x7FFFFFFF))
        return x.value;
    if (!(x.bits & 0x7FFFFFFF))
        return __negsf2(y.value);
    y.bits ^= 0x80000000;
    return __addsf3(a, y.value);
}
