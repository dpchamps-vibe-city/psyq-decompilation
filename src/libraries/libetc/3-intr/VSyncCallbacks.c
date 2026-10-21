#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

void VSyncCallbacks(void) {
    ((void (*)(void))D_00001890->unk14)();
}
