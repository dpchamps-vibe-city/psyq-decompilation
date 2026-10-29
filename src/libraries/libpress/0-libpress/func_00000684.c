#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include "libpress_internal.h"

static int func_00000684(char *msg) {
    printf(RO_STR_00000708 + 60, msg);
    *D_0000089C = 0x80000000;
    *D_00000870 = 0;
    *D_0000087C = 0;
    (void)*D_0000087C;
    *D_0000089C = 0x60000000;
    return 0;
}
