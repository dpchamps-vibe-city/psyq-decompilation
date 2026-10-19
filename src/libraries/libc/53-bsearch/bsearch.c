/* Original TU: library-input/psyq/LIB/LIBC.LIB[53] BSEARCH.OBJ
 * sha256: 93e7a1ae41ad0095d2c731ce675fdbabf6873acb4dd159f5c32b323e8e007127
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: bsearch
 */
#include "common.h"
#include "include_asm.h"

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
