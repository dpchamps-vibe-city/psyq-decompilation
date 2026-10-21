#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <memory.h>
#include <stdio.h>
#include <strings.h>

static s32 func_0000097C(s32 arg0, s32 arg1, u8 *arg2) {
    DslLOC sp10;
    s32 temp_v0;

    DsIntToPos(arg1, &sp10);
    DsRead(&sp10, arg0, (u_long *) arg2, 0x80);
    do {
        temp_v0 = DsReadSync(NULL);
    } while (temp_v0 > 0);
    return temp_v0 == 0;
}
