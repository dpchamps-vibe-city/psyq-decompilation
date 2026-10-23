#include "common.h"
#include <stdio.h>

extern char RO_STR_000000E0[];

s32 print_matrix(s16 *arg0) {
    return printf(RO_STR_000000E0, arg0[0], arg0[1], arg0[2], arg0[3], arg0[4], arg0[5], arg0[6], arg0[7], arg0[8]);
}
