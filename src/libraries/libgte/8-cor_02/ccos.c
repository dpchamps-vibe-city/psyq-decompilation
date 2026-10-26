#include "common.h"

extern void csincos(int a, int *s, int *c);

int ccos(int a)
{
    int s, c;

    if (a < 0)
        a = -a;
    a %= 4096;
    if (a >= 0 && a < 1024) {
        csincos(a, &s, &c);
        return c;
    } else if (a >= 1024 && a < 2048) {
        csincos(2047 - a, &s, &c);
        return -c;
    } else if (a >= 2048 && a < 3072) {
        csincos(a - 2048, &s, &c);
        return -c;
    } else if (a >= 3072 && a < 4096) {
        csincos(4095 - a, &s, &c);
        return c;
    }
}
