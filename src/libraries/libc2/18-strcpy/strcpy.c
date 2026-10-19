/* member: LIBC2.LIB STRCPY.OBJ */
#include "common.h"

char *strcpy(char *dest, const char *src) {
    char *dst;
    char *ret;
    char c;

    ret = 0;
    if (dest != 0) {
        dst = dest;
        if (src != 0) {
            c = *src;
            src += 1;
            dest += 1;
            *dst = c;
            if (c != 0) {
                do {
                    c = *src;
                    src += 1;
                    *dest = c;
                    dest += 1;
                } while (c != 0);
            }
            ret = dst;
        }
    }
    return ret;
}
