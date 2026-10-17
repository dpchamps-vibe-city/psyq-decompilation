#include "common.h"

s8 *strpbrk(s8 *arg0, s8 *arg1) {
    s8 *start = arg0;
    s8 *q;
    s8 *ret;

    while (*arg0 != 0) {
        for (q = arg1; *q != 0; q++) {
            if (*q == *arg0)
                return arg0;
        }
        arg0++;
    }
    ret = (s8 *)*arg0;
    if (start == arg0)
        ret = 0;
    return ret;
}
