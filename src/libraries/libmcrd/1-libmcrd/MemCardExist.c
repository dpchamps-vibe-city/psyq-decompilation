#include "common.h"
#include <libmcrd.h>
#include <stdio.h>
#include "libmcrd_internal.h"

static s32 func_000001FC(s32 *);

long MemCardExist(long chan)
{
    McrdState *mcrd = (McrdState *)&B_00001B78;

    if (mcrd->unk00 > 0) {
        printf(RO_STR_00001958);
        return 0;
    }
    mcrd->unk00 = 1;
    mcrd->unk04 = 0;
    mcrd->unk08 = 0;
    mcrd->unk10 = chan;
    UserFuncOpen(func_000001FC);
    return 1;
}
