#include "common.h"
#include <libmath.h>

extern int __eqdf2(double, double);
extern int __ledf2(double, double);
extern int __gedf2(double, double);
extern int __ltdf2(double, double);
extern int __fixdfsi(double);
extern double __floatsidf(int);
extern double __muldf3(double, double);
extern double __divdf3(double, double);
extern int _err_math(int, int);

double pow(double x, double y)
{
    double result, base;
    int exponent, negative, n;

    if (x == 0.0) {
        if (y <= 0.0) {
            _err_math(33, 5);
            return 1.0;
        }
        return 0.0;
    }
    if (y <= 2147483647.0 && y >= -2147483647.0) {
        exponent = (int)y;
        if (y == (double)exponent) {
            base = x;
            negative = 0;
            n = exponent;
            if (exponent < 0) {
                negative = 1;
                n = -exponent;
            }
            result = 1.0;
            if (negative == 1)
                base = 1.0 / x;
            do {
                if (n & 1)
                    result = result * base;
                n /= 2;
                if (n != 0)
                    base = base * base;
            } while (n != 0);
            return result;
        }
    }
    if (x < 0.0) {
        _err_math(33, 5);
        return 0.0;
    }
    return exp(y * log(x));
}
