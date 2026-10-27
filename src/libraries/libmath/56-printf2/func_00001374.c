#include "common.h"
#include <libmath.h>

static signed char *func_00001374(double fract, int *expcnt,
    signed char *start, signed char *end, signed char ch, signed char *signp)
{
    double tmp;

    if (fract != 0.0)
        modf(fract * 10.0, &tmp);
    else
        tmp = ch - '0';
    if (tmp > 4.0) {
        for (;;) {
            if (*end == '.')
                --end;
            if (++*end <= '9')
                break;
            *end = '0';
            if (end == start) {
                if (expcnt) {
                    *start = '1';
                    ++*expcnt;
                } else {
                    start[-1] = '1';
                    --start;
                }
                break;
            }
            --end;
        }
    } else if (*signp == '-') {
        for (;;) {
            if (*end == '.')
                --end;
            if (*end != '0')
                break;
            if (end == start)
                *signp = 0;
            --end;
        }
    }
    return start;
}
