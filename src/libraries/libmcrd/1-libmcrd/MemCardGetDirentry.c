#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include <string.h>
#include "libmcrd_internal.h"

extern char RO_STR_00001AFC[];
extern s32 B_00001B88;

extern void func_000018FC(long port, char *path);
static s32 func_000017FC(s32);
static s32 func_00000580(s32 *);

extern MemCB B_00001BD0;

long MemCardGetDirentry(long chan, char *name, struct DIRENTRY *dir, long *files, long ofs, long max)
{
    McrdState *mcrd = (McrdState *)&B_00001B78;
    char path[32];
    struct DIRENTRY entry;
    struct DIRENTRY *ret;
    long result;
    long retries;
    long i;
    long n;
    long command = 2;

    if (mcrd->unk00 != 0) {
        printf(RO_STR_00001AFC);
        return -1;
    }
    func_000018FC(chan, path);
    strcat(path, name);
    result = 0;
    retries = 0;
    mcrd->unk0C |= 1 << chan;
    n = 0;
    for (i = 0; i < ofs + max; i++) {
        McrdState *active = mcrd;
        if (i == 0) {
            for (;;) {
                _clr_card_event();
                ret = firstfile(path, &entry);
                if (ret != NULL)
                    break;
                result = func_000017FC(_get_card_event_x());
                if (result == 0)
                    break;
                if (++retries < 4)
                    continue;
                B_00001BD0 = MemCardCallback(NULL);
                if (active->unk00 > 0) {
                    printf(RO_STR_00001958);
                } else {
                    active->unk00 = command;
                    active->unk04 = 0;
                    active->unk08 = 0;
                    B_00001B88 = chan;
                    UserFuncOpen(func_00000580);
                }
                MemCardSync(0, NULL, &result);
                MemCardCallback(B_00001BD0);
                return result;
            }
        } else {
            ret = nextfile(&entry);
        }
        if (ret == NULL)
            break;
        if (i < ofs)
            continue;
        if (dir != NULL) {
            dir[n] = entry;
            n++;
        }
    }
    if (files != NULL)
        *files = n;
    return 0;
}
