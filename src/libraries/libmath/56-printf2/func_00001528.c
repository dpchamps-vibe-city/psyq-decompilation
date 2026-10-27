#include "common.h"
#include <libmath.h>

static signed char *func_00001528(signed char *p, int n, unsigned char fmt)
{
    signed char buf[308];
    signed char *t;

    *p++ = fmt;
    if (n < 0) {
        n = -n;
        *p++ = '-';
    } else
        *p++ = '+';
    t = buf + 308;
    if (n >= 10) {
        do {
            *--t = n % 10 + '0';
            n /= 10;
        } while (n >= 10);
        *--t = n + '0';
        while (t < buf + 308)
            *p++ = *t++;
    } else {
        *p++ = '0';
        *p++ = n + '0';
    }
    return p;
}
