#include "common.h"

extern int prnt();

int printf(const char *fmt, int a1, int a2, int a3) {
    int *ap = &a1;

    (void)&fmt;
    ap[1] = a2;
    ap[2] = a3;
    return prnt(1, fmt, ap);
}
