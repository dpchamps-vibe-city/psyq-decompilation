#include "common.h"

s8 *strstr(s8 *arg0, s8 *arg1) {
    s8 *p;
    s8 *q;
    s8 *start;
    s32 flag;

    p = arg0;
    flag = 0;
    q = arg1;
    start = arg0;
    while (*p != 0) {
        if (*p == *q) {
            q++;
            if (*q == 0) {
                return start;
            }
            if (flag == 0) {
                start = p;
                flag = 1;
            }
        } else {
            q = arg1;
            flag = 0;
        }
        p++;
    }
    return 0;
}
