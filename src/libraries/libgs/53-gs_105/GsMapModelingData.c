#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsMapModelingData(unsigned long *p) {
    s32 i;
    s32 n;

    if (!(p[0] & 1)) {
        p[0] |= 1;
        p++;
        i = 0;
        n = *p++;
        if (n > 0) {
            do {
                p[i * 7 + 0] = p[i * 7 + 0] + (unsigned long) p;
                p[i * 7 + 2] = p[i * 7 + 2] + (unsigned long) p;
                p[i * 7 + 4] = p[i * 7 + 4] + (unsigned long) p;
                i++;
            } while (i < n);
        }
    }
}
