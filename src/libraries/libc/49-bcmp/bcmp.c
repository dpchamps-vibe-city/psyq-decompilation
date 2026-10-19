/* library-input/psyq/LIB/LIBC.LIB[49] BCMP.OBJ */
#include "common.h"

int bcmp(unsigned char *s1, unsigned char *s2, int n) {
    int i;

    for (i = n - 1; i != -1; i--) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}
