#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>

static void func_00000278(u_char, u_char *, u_long *);

static void func_0000022C(u_char arg0, u_char *arg1) {
    if ((arg0 & 0xFF) == 2) {
        DsStartReadySystem(func_00000278, 0);
        return;
    }
    GD_disk_kind = 2;
    GD_retry = 2;
}
