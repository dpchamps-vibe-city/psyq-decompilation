#include "common.h"
#include <libmcrd.h>

extern volatile long B_00001B68[];
extern volatile long B_00001B6C[];

long MemCardSync(long mode, long *cmds, long *rslt)
{
    McrdState *mcrd = (McrdState *)&B_00001B78;
    long cmd;
    long result;

    if (mcrd->unk00 == 0 && mcrd->unk08 == 0)
        return -1;
    cmd = mcrd->unk00;
    result = mcrd->unk04;
    if (mode == 0) {
        if (mcrd->unk08 == 0) {
            volatile long *done = &mcrd->unk08;
            do {
            } while (*done == 0);
        }
        if (rslt != 0)
            *rslt = B_00001B6C[0];
        if (cmds != 0)
            *cmds = B_00001B68[0];
        ((McrdState *)&B_00001B78)->unk08 = 0;
        return 1;
    }
    if (mcrd->unk08 == 0) {
        if (rslt != 0)
            *rslt = result;
        if (cmds != 0)
            *cmds = cmd;
        return 0;
    }
    if (rslt != 0)
        *rslt = B_00001B6C[0];
    if (cmds != 0)
        *cmds = B_00001B68[0];
    mcrd->unk08 = 0;
    return 1;
}
