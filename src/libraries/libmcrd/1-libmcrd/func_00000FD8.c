#include "common.h"
#include <libapi.h>
#include "libmcrd_internal.h"

extern s32 D_00001B38;
static s32 func_00000AAC(s32 *);

s32 func_00000FD8(s32 *arg)
{
    volatile long *event;
    long *fd;
    McrdState *mcrd;
    long descriptor;

    switch (arg[0]) {
    case 0:
        D_00001B38 = 0;
        UserFuncOpen(func_000001FC);
        arg[0] = 10;
        break;
    case 10:
        event = &((McrdState *)&B_00001B78)->unk04;
        if (*event != 0)
            return 1;
        descriptor = open((char *)(event + 8), 0x8001);
        *(long *)(event + 4) = descriptor;
        if (descriptor < 0) {
            mcrd = (McrdState *)(event - 1);
            mcrd->unk04 = 5;
            return 1;
        }
    case 11:
        arg[0] = 20;
        UserFuncOpen(func_00000AAC);
        break;
    case 20:
        fd = &((McrdState *)&B_00001B78)->unk14;
        close(*fd);
        *fd = -1;
        return 1;
    }
    return 0;
}
