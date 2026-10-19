#include "common.h"

int memcmp(const void *s1, const void *s2, unsigned int n) {
    const u8 *p1 = s1;
    const u8 *p2 = s2;
    int i;

    for (i = n - 1; i != -1; i--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}
