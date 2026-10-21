#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>

static void func_00000344(u_char, u_char *, u_long *);
extern s8 B_000008EF;

void func_000002F4(u_char arg0, u_char *arg1) {
    s32 var_v1;
    s8 *var_v0;

    if ((arg0 & 0xFF) == 2) {
        var_v1 = 7;
        var_v0 = &B_000008EF;
        do {
            *var_v0 = 0;
            var_v1 -= 1;
            var_v0 -= 1;
        } while (var_v1 >= 0);
        DsStartReadySystem(func_00000344, 0);
    }
}
