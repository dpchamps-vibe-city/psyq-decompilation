#include "common.h"

extern int __ltdf2(double, double);
extern int __eqdf2(double, double);
extern double __negdf2(double);
extern double __adddf3(double, double);
extern double __muldf3(double, double);
extern double __divdf3(double, double);
extern float __truncdfsf2(double);
extern double __extendsfdf2(float);
extern float __addsf3(float, float);
extern float __mulsf3(float, float);
extern float __divsf3(float, float);

double hypot(double x, double y)
{
    float t;
    int i;

    if (x < 0.0)
        x = -x;
    if (y < 0.0)
        y = -y;
    if (x < y) {
        t = (float)x;
        x = y;
        y = t;
    }
    if (y == 0.0)
        return x;
    for (i = 0; i < 3; i++) {
        t = y / x;
        t = t * t;
        t = t / (t + 4.0f);
        x = x + (x + x) * t;
        y = y * t;
    }
    return x;
}
