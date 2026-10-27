#include "common.h"

int __gtsf2(int a, int b)
{
    int sign;
    int e1;
    int e2;
    int m1;
    int m2;

    if ((a == b) || (((a & 0x7FFFFFFF) == 0) && ((b & 0x7FFFFFFF) == 0)))
        return 0;
    sign = a & 0x80000000;
    if (sign != (b & 0x80000000))
        goto greater;
    e1 = (a >> 23) & 0xFF;
    e2 = (b >> 23) & 0xFF;
    if (e2 < e1)
        goto greater;
    if (e1 != e2)
        goto less;
    m1 = (a & 0x7FFFFF) | 0x800000;
    m2 = (b & 0x7FFFFF) | 0x800000;
    if (m2 < m1)
        goto greater;
less:
    return (unsigned int)a >= 0x80000000;
greater:
    return sign == 0;
}
