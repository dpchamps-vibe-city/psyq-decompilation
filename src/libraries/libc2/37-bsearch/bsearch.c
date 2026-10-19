/* LIBC2.LIB BSEARCH.OBJ */
#include "common.h"

void *bsearch(const unsigned char *key, const unsigned char *base, unsigned int nmemb, unsigned int size, int (*compar)()) {
    unsigned int low;
    unsigned int high;
    unsigned int mid;
    const unsigned char *p;
    int c;

    low = 0;
    high = nmemb;
    while (low < high) {
        mid = (low + high) >> 1;
        p = base + size * mid;
        c = compar(p, key);
        if (c < 0) {
            low = mid + 1;
        } else if (c > 0) {
            high = mid;
        } else {
            return (void *)p;
        }
    }
    return 0;
}
