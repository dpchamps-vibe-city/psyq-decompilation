#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include <string.h>
#include "libmcrd_internal.h"

extern s32 B_00001B78;
extern char RO_STR_00001A54[];
extern char RO_STR_00001AFC[];

extern void func_000018FC(long port, char *path);
static s32 func_00000FD8(s32 *);

long MemCardReadFile(long port, char *name, unsigned long *adrs, long ofs, long bytes)
{
    McrdState *mcrd = (McrdState *)&B_00001B78;
    char *message;

    if (mcrd->unk00 > 0) {
        message = RO_STR_00001AFC;
        goto denied;
    }
    if (mcrd->unk14 >= 0) {
        message = RO_STR_00001A54;
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
    func_000018FC(port, (char *)&mcrd->unk18[3]);
    strcat((char *)&mcrd->unk18[3], name);
    mcrd->unk00 = 3;
    mcrd->unk04 = 0;
    mcrd->unk08 = 0;
    mcrd->unk18[0] = ofs;
    mcrd->unk18[2] = (long)adrs;
    mcrd->unk18[1] = bytes;
    mcrd->unk10 = port;
    UserFuncOpen(func_00000FD8);
    return 1;

denied:
    printf(message);
    return 0;
}
