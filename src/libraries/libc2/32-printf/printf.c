/* member: LIBC2.LIB PRINTF.OBJ */
#include "common.h"

extern int prnt();

int printf(const char *format, int arg1, int arg2, int arg3) {
    int *ap = &arg1;

    (void)&format;
    ap[1] = arg2;
    ap[2] = arg3;
    return prnt(1, format, ap);
}