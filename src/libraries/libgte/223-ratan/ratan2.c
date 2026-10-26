#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern short ratan_tbl[];

long ratan2(long y, long x) {
    int a;
    int b;
    int t;
    int r;

    a = 0;
    b = 0;
    if (x < 0) {
        a = 1;
        x = -x;
    }
    if (y < 0) {
        b = 1;
        y = -y;
    }
    if (x == 0 && y == 0)
        return 0;
    if (y < x) {
        if (y & 0x7FE00000)
            t = y / (x >> 10);
        else
            t = (y << 10) / x;
        r = ratan_tbl[t];
    } else {
        if (x & 0x7FE00000)
            t = x / (y >> 10);
        else
            t = (x << 10) / y;
        r = 0x400 - ratan_tbl[t];
    }
    if (a)
        r = 0x800 - r;
    if (b)
        r = -r;
    return r;
}
