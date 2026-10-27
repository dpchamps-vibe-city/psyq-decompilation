#include "common.h"
#include <libmath.h>

static signed char *func_00001374(double, int *, signed char *, signed char *, signed char, signed char *);
static signed char *func_00001528(signed char *, int, unsigned char);

static int func_00000AD8(double number, int prec, int flags,
    signed char *signp, unsigned char fmt, signed char *startp, signed char *endp)
{
    double integer, tmp, fract;
    int expcnt, gformat;
    signed char *p, *t;
    int dotrim;

    gformat = 0;
    expcnt = 0;
    fract = modf(number, &integer);
    p = ++startp;
    t = endp - 1;
    for (; integer != 0.0; ++expcnt) {
        tmp = modf(integer / 10.0, &integer);
        *t-- = (int)((tmp + 0.01) * 10.0) + '0';
    }
    switch (fmt) {
    case 'f':
        ++t;
        if (expcnt) {
            while (t < endp)
                *p++ = *t++;
        } else
            *p++ = '0';
        if (prec || (flags & 8))
            *p++ = '.';
        if (fract != 0.0) {
            if (prec) {
                do {
                    fract = modf(fract * 10.0, &tmp);
                    *p++ = (int)tmp + '0';
                } while (--prec && fract != 0.0);
            }
            if (fract != 0.0)
                startp = func_00001374(fract, 0, startp, p - 1, 0, signp);
        }
        while (prec--)
            *p++ = '0';
        break;
    case 'E':
    case 'e':
exponential:
        ++t;
        if (expcnt) {
            *p++ = *t;
            if (prec || (flags & 8))
                *p++ = '.';
            while (prec && ++t < endp) {
                *p++ = *t;
                --prec;
            }
            if (!prec && ++t < endp) {
                fract = 0.0;
                startp = func_00001374(fract, &expcnt, startp, p - 1, *t, signp);
            }
            --expcnt;
        } else if (fract != 0.0) {
            expcnt = -1;
            for (;;) {
                fract = modf(fract * 10.0, &tmp);
                if (tmp != 0.0)
                    break;
                --expcnt;
            }
            *p++ = (int)tmp + '0';
            if (prec || (flags & 8))
                *p++ = '.';
        } else {
            *p++ = '0';
            if (prec || (flags & 8))
                *p++ = '.';
        }
        if (fract != 0.0) {
            if (prec) {
                do {
                    fract = modf(fract * 10.0, &tmp);
                    *p++ = (int)tmp + '0';
                } while (--prec && fract != 0.0);
            }
            if (fract != 0.0)
                startp = func_00001374(fract, &expcnt, startp, p - 1, 0, signp);
        }
        while (prec--)
            *p++ = '0';
        if (gformat && !(flags & 8)) {
            while (p > startp && *--p == '0')
                ;
            if (*p == '.')
                --p;
            ++p;
        }
        p = func_00001528(p, expcnt, fmt);
        break;
    case 'G':
    case 'g':
        if (!prec)
            prec = 1;
        if (expcnt > prec || (!expcnt && fract != 0.0 && fract < 0.0001)) {
            --prec;
            fmt -= 2;
            gformat = 1;
            goto exponential;
        }
        if (expcnt) {
            ++t;
            while (t < endp) {
                --prec;
                *p++ = *t++;
            }
        } else
            *p++ = '0';
        if (prec || (flags & 8)) {
            dotrim = 1;
            *p++ = '.';
        } else
            dotrim = 0;
        if (fract != 0.0) {
            if (prec) {
                do {
                    fract = modf(fract * 10.0, &tmp);
                    *p++ = (int)tmp + '0';
                } while (tmp == 0.0);
                --prec;
                for (; prec && fract != 0.0; --prec) {
                    fract = modf(fract * 10.0, &tmp);
                    *p++ = (int)tmp + '0';
                }
            }
            if (fract != 0.0)
                startp = func_00001374(fract, 0, startp, p - 1, 0, signp);
        }
        if (flags & 8) {
            while (prec--)
                *p++ = '0';
        } else if (dotrim) {
            while (p > startp && *--p == '0')
                ;
            if (*p != '.')
                ++p;
        }
        break;
    }
    return p - startp;
}
