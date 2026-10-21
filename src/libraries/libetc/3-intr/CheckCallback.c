#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

extern u16 D_0000080A;

int CheckCallback(void) {
    return (s32) D_0000080A;
}
