#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>

extern s32 D_000005AC;

static void func_000002B4(void) {
    DsEndReadySystem();
    DsCommand(9U, NULL, NULL, -1);
    D_000005AC = -1;
}
