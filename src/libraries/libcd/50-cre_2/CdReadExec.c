#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <kernel.h>

extern struct EXEC exec __asm__("$LB_00000150");

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
    exec = *(struct EXEC *)(p + 4);
    exec.s_addr = 0;
    exec.s_size = 0;
    return &exec;
}
