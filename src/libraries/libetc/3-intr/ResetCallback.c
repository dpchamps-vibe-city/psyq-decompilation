#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

int ResetCallback(void) {
    return ((int (*)(void))D_00001890->unkC)();
}
