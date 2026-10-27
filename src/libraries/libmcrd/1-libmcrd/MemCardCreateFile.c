#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include <string.h>
#include "libmcrd_internal.h"

extern char RO_STR_00001AFC[];
extern long _card_create2(long chan, char *file, long blocks);
extern void func_000018FC(long port, char *path);
static s32 func_000017FC(s32);

long MemCardCreateFile(long chan, char *file, long blocks)
{
    McrdState *mcrd = (McrdState *)&B_00001B78;
    char path[32];
    long result;

    if (mcrd->unk00 != 0) {
        printf(RO_STR_00001AFC);
        return -1;
    }
    goto body;
ret7:
    return 7;
ret4:
    return 4;
ret6:
    return 6;
body:
    do {
        func_000018FC(chan, path);
        strcat(path, file);
        mcrd->unk0C |= 1 << chan;
    } while (0);
    result = _card_create2(chan, file, blocks);
    if (result != 0) {
        if (result == -1)
            goto ret7;
        if (result == -2)
            goto ret4;
        if (result == -3)
            goto ret6;
        if (result == 4)
            return 2;
        return func_000017FC(result);
    }
    return 0;
}
