#include "common.h"

int csqrt(int a) {
    int n;
    int s;
    int x;

    if (a == 0) {
        return 0;
    }
    n = 8 - Lzc(a);
    if (n >= 0) {
        s = n >> 1;
        x = a >> (s << 1);
    } else {
        s = (n >> 1) + 1;
        x = a << -(s << 1);
    }
    s -= 6;
    if (s >= 0) {
        return csqrt_1(x) << s;
    } else {
        return csqrt_1(x) >> -s;
    }
}
