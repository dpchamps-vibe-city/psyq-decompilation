#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <libetc.h>

extern s32 GD_disk_kind;
extern volatile s32 GD_retry;
extern char RO_STR_00000300[];

static void func_00000278(u_char arg0, u_char *arg1, u_long *arg2) {
    u_char buf[8];

    if ((arg0 & 0xFF) == 1) {
        DsGetSector(buf, 2);
        if (strncmp((char *)buf + 1, RO_STR_00000300, 5) == 0) {
            GD_disk_kind = 4;
        } else {
            GD_disk_kind = 2;
        }
    } else {
        GD_disk_kind = 2;
        GD_retry = 1;
    }
    DsEndReadySystem();
}
