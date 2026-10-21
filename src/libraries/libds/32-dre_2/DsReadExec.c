#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <kernel.h>

extern struct EXEC B_00000160;

struct EXEC *DsReadExec(char *file) {
    u_long buf[0x200];
    u_long *p = buf;
    int ret;

    if (DsReadFile(file, p, 0x800) == 0) {
        return 0;
    }
    while ((ret = DsReadSync(0)) != 0) {
        if (ret < 0) {
            return 0;
        }
    }
    if (DsReadFile(0, (u_long *)p[6], 0) == 0) {
        return 0;
    }
    while ((ret = DsReadSync(0)) != 0) {
        if (ret < 0) {
            return 0;
        }
    }
    B_00000160 = *(struct EXEC *)(p + 4);
    B_00000160.s_addr = 0;
    B_00000160.s_size = 0;
    return &B_00000160;
}
