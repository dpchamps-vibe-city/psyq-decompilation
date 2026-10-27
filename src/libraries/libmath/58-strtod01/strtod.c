#include "common.h"
#include <libmath.h>

extern char _ctype_[];
extern s8 toupper(s8);
#define isdigit(c) ((_ctype_ + 1)[(u8)(c)] & 4)

extern double __adddf3(double, double);
extern double __divdf3(double, double);
extern double __floatsidf(int);
extern int __gedf2(double, double);
extern int __gtdf2(double, double);
extern int __ltdf2(double, double);
extern double __muldf3(double, double);
extern double __negdf2(double);
extern int _err_math(int, int);

static s8 *func_00000544(s8 *, int *);

#define MIN_VALUE 2.2250738585072009e-308
#define MAX_VALUE 1.0e400

double strtod(char *s, char **endptr)
{
    s8 *p;
    s8 *start;
    double value;
    double scale;
    int neg;
    int dot;
    int exp;
    int e;

    exp = 0;
    value = 0.0;
    dot = 0;
    neg = 0;
    p = func_00000544((s8 *)s, &neg);
    start = p;
    scale = 10.0;
    while (*p) {
        if (isdigit(*p)) {
            if (dot)
                exp--;
            value = value * 10.0 + (*p - '0');
        } else if (*p == '.') {
            if (dot)
                break;
            dot = 1;
        } else {
            break;
        }
        p++;
    }
    if (neg)
        value = -value;
    neg = 0;
    if (toupper(*p) == 'E') {
        p++;
        if (*p == '+') {
            p++;
        } else if (*p == '-') {
            neg = 1;
            p++;
        }
        e = 0;
        while (isdigit(*p))
            e = e * 10 + (*p++ - '0');
        if (neg)
            exp -= e;
        else
            exp += e;
    }
    neg = 1;
    if (exp < 0) {
        exp = -exp;
    } else {
        neg = 0;
    }
    while (exp) {
        if (exp & 1) {
            if (neg) {
                if (value >= 0.0) {
                    if (value < scale * MIN_VALUE) {
                        value = 0.0;
                        _err_math(34, 30);
                        break;
                    }
                }
                if (value < 0.0 && value > scale * -MIN_VALUE) {
                    value = 0.0;
                    _err_math(34, 30);
                    break;
                }
                value = value / scale;
            } else {
                if (value >= 0.0) {
                    if (value > MAX_VALUE / scale) {
                        value = MAX_VALUE;
                        _err_math(34, 30);
                        break;
                    }
                }
                if (value < 0.0 && value < -MAX_VALUE / scale) {
                    value = -MAX_VALUE;
                    _err_math(34, 30);
                    break;
                }
                value = value * scale;
            }
        }
        if (scale > MAX_VALUE / scale) {
            if (neg)
                value = 0.0;
            else if (value >= 0.0)
                value = MAX_VALUE;
            else
                value = -MAX_VALUE;
            _err_math(34, 30);
            break;
        }
        scale = scale * scale;
        exp = exp / 2;
    }
    if (endptr != 0) {
        if (p == start)
            *endptr = s;
        else
            *endptr = (char *)p;
    }
    return value;
}
