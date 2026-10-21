#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

int RestartCallback(void) {
    return ((s32 (*)()) D_00001890->unk18)();
}
