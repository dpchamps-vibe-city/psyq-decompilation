#include <libmath.h>

double exp(double x)
{
    double scaled, term, sum, previous;
    int exponent, negative = 0, i;

    scaled = x / 0.6931471805599453;
    if (x >= 0.0)
        exponent = (int)(scaled + 0.5);
    else
        exponent = (int)(scaled + -0.5);
    x -= exponent * 0.6931471805599453;
    if (x >= 0.0)
        negative = 0;
    else {
        negative = 1;
        x = -x;
    }
    sum = x + 1.0;
    term = x;
    i = 2;
    do {
        previous = sum;
        term *= x / i;
        sum += term;
        i++;
    } while (sum != previous);
    if (negative)
        sum = 1.0 / sum;
    return ldexp(sum, exponent);
}
