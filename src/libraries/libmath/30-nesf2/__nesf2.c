#include "common.h"

int __nesf2(int a, int b)
{
    int v;

    if ((a == b) || (((a & 0x7FFFFFFF) == 0) && ((b & 0x7FFFFFFF) == 0)))
        v = 0;
    else
        v = 1;
    return v;
}
