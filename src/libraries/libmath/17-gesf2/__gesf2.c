#include "common.h"

int __gesf2(int a, int b)
{
    int sign;
    int e1;
    int e2;
    int m1;
    int m2;

    if (a != b && ((a & 0x7FFFFFFF) || (b & 0x7FFFFFFF))) {
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
        if (m1 < m2)
            goto less;
greater:
        if (sign)
            return -1;
    }
    return 0;
less:
    if (a < 0)
        return 0;
    return -1;
}
