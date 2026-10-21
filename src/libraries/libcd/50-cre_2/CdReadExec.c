#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <kernel.h>

extern struct EXEC B_00000150;

struct EXEC *CdReadExec(char *file) {
    u_long buf[0x200];
    u_long *p = buf;

    if (CdReadFile(file, p, 0x800) == 0) {
        return 0;
    }
    if (CdReadSync(0, 0) != 0) {
        return 0;
    }
    if (CdReadFile(0, (u_long *)p[6], 0) == 0) {
        return 0;
    }
    if (CdReadSync(0, 0) != 0) {
        return 0;
    }
    B_00000150 = *(struct EXEC *)(p + 4);
    B_00000150.s_addr = 0;
    B_00000150.s_size = 0;
    return &B_00000150;
}
