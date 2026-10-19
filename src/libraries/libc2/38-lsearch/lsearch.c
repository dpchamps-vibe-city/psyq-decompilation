/* LIBC2.LIB LSEARCH.OBJ */
#include "common.h"

void *lsearch(const unsigned char *key, unsigned char *base, unsigned int *nelp, unsigned int width, int (*compar)()) {
    while (compar(key, base) != 0) {
        base += width;
    }
    return base;
}
