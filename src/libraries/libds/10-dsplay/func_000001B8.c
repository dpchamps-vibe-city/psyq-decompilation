#include "common.h"
#include <sys/types.h>
#include <libds.h>
#include <stdio.h>

extern DsPlayData D_000005A8;
extern char RO_STR_0000058C[];

s32 ER_active(void);

static void func_000002F4(u_char, u_char *);

static void func_000001B8(void) {
    DslLOC pos;

    if (D_000005A8.status < 0) {
        if (CD_debug > 0) {
            printf(RO_STR_0000058C - 24, D_000005A8.status);
        }
        return;
    }
    if (ER_active() != 0) {
        D_000005A8.status = -1;
        return;
    }
    pos = D_000005A8.toc[D_000005A8.tracks[D_000005A8.status]];
    D_000005A8.field0 = DsPacket(5, &pos, 3, func_000002F4, -1);
    if (D_000005A8.field0 == 0) {
        if (CD_debug > 0) {
            puts(RO_STR_0000058C);
        }
        D_000005A8.status = -1;
    }
}
