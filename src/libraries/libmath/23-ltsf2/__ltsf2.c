#include "common.h"

int __ltsf2(int a, int b)
{
    int sign;
    int e1;
    int e2;
    int m1;
    int m2;

    if ((a == b) || (((a & 0x7FFFFFFF) == 0) && ((b & 0x7FFFFFFF) == 0)))
        return 0;
    sign = a & 0x80000000;
    if (sign != (b & 0x80000000)) {
        if (sign)
            return -1;
        return 0;
    }
    e1 = (a >> 23) & 0xFF;
    e2 = (b >> 23) & 0xFF;
    if (e1 < e2)
        goto less;
    if (e1 != e2)
        goto greater;
    m1 = (a & 0x7FFFFF) | 0x800000;
    m2 = (b & 0x7FFFFF) | 0x800000;
    if (m1 >= m2)
        goto greater;
less:
    if (sign)
        return 0;
    return -1;
greater:
    if (a < 0)
        return -1;
    return 0;
}
