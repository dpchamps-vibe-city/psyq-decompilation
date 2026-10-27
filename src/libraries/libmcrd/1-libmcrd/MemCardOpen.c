INCLUDE_ASM("build/libraries/nonmatchings/libmcrd_1", MemCardOpen);


/* PARKED by /auto_decompilation_loop on 2026-10-27T17:36:54.249Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcrd_1::MemCardOpen.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include <strings.h>
#include "libmcrd_internal.h"

extern long B_00001B8C;
extern MemCB B_00001BD0;
extern char RO_STR_00001A54[];
extern void _clr_card_event(void);
static void func_000018FC(long, char *);
static s32 T_00000580(s32 *);

long MemCardOpen(long chan, char *file, long flag)
{
    long result;
    long *fd = &((McrdState *)&B_00001B78)->unk14;
    char *path;
    McrdState *state;
    long descriptor;
    long retries = 0;

    if (fd[0] >= 0) {
        printf(RO_STR_00001A54);
        return -1;
    }
    path = (char *)(fd + 4);
    func_000018FC(chan, path);
    strcat(path, file);
    state = (McrdState *)&B_00001B78;
    fd[-1] = chan;
    do {
        do {
            descriptor = open(path, 1);
            if (descriptor >= 0)
                goto opened;
            B_00001BD0 = MemCardCallback(0);
            if (*(long *)(path - 0x24) > 0) {
                printf(RO_STR_00001958);
            } else {
                *(long *)(path - 0x24) = 2;
                state->unk04 = 0;
                state->unk08 = 0;
                *(long *)((char *)B_00001B48 + 0x40) = chan;
                UserFuncOpen(T_00000580);
            }
            MemCardSync(0, 0, &result);
            MemCardCallback(B_00001BD0);
        } while (result == 3);
        if (result != 2)
            break;
        ++retries;
    } while (retries < 5);
    if (result == 0)
        result = 5;
    return result;

opened:
    close(descriptor);
    _clr_card_event();
    *(long *)(path - 0x10) = open(path, flag | 0x8000);
    return 0;
}
#endif
