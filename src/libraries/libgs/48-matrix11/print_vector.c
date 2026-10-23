#include "common.h"
#include <stdio.h>

extern char RO_STR_000000A0[];

s32 print_vector(s32 *arg0) {
    return printf(RO_STR_000000A0, arg0[5], arg0[6], arg0[7]);
}
