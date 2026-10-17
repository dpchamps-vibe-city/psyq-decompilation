#include "common.h"

s32 bcmp(u8 *s1, u8 *s2, s32 n) {
    s32 i;

    for (i = n - 1; i != -1; i--) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}
