/* Original TU: LIBC2.LIB STRNCPY.OBJ */
#include "common.h"

char *strncpy(char *dst, const char *src, int n) {
    char *dst_orig;
    char *ret;
    int i;
    int c;

    ret = 0;
    if (dst != 0) {
        i = 0;
        if (src != 0) {
            dst_orig = dst;
            if (n > 0) {
                for (;;) {
                    c = *src++;
                    *dst++ = c;
                    if (c == 0) {
                        i += 1;
                        while (i < n) {
                            *dst++ = 0;
                            i += 1;
                        }
                        return dst_orig;
                    }
                    i += 1;
                    if (i >= n) {
                        break;
                    }
                }
            }
            ret = dst_orig;
        }
    }
    return ret;
}
