#include "common.h"
#include <stdio.h>

extern char B_000000C8[];
extern char RO_STR_000000B8[];

char *itoa(int arg0) {
    sprintf(B_000000C8, RO_STR_000000B8, arg0);
    return B_000000C8;
}
