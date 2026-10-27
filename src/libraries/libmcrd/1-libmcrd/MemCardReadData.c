#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include "libmcrd_internal.h"

static s32 func_00000AAC(s32 *);

long MemCardReadData(unsigned long *adrs, long ofs, long bytes)
{
    long *fd = &((McrdState *)&B_00001B78)->unk14;
    McrdState *mcrd;
    char *message;

    if (*fd < 0) {
        message = RO_STR_00001A7C;
        goto denied;
    }
    mcrd = (McrdState *)(fd - 5);
    if (mcrd->unk00 > 0) {
        message = RO_STR_00001958;
        goto denied;
    }
    if (bytes & 0x7F) {
        message = RO_STR_00001AA0;
        goto denied;
    }
    if (ofs & 0x7F) {
        message = RO_STR_00001ACC;
        goto denied;
    }
    mcrd->unk00 = 5;
    mcrd->unk04 = 0;
    mcrd->unk08 = 0;
    mcrd->unk18[0] = ofs;
    mcrd->unk18[2] = (long)adrs;
    mcrd->unk18[1] = bytes;
    UserFuncOpen(func_00000AAC);
    return 1;

denied:
    printf(message);
    return 0;
}
