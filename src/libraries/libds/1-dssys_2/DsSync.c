INCLUDE_ASM("build/libraries/nonmatchings/libds_1", DsSync);


/* PARKED by /auto_decompilation_loop on 2026-10-21T02:23:53.067Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libds_1::DsSync.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"

typedef struct {
    s32 active;
    s32 w4;
    s32 w8;
    s32 wC;
} DsSyncEntry;

typedef struct {
    s32 active;
    u8 command;
    u8 param[4];
    u8 pad[3];
    s32 unkC;
} DsSyncCmd;

extern DsSyncEntry DsSyncOut_ __asm__("B_00001578");
extern DsSyncEntry DsSyncQ_[] __asm__("B_00001688");
extern s32 DsSyncIndex_ __asm__("B_00001708");

void DS_sync(u8 *arg0);
void rescpy(u8 *dst, u8 *src);

#define DS_SYNC_FINISHED 0x07
#define DS_SYNC_NORESULT 0x06

int DsSync(int id, unsigned char *result) {
    DsSyncEntry *p;
    DsSyncCmd *cmd;
    s32 i;
    s32 j;
    s32 n;

    if (id != 0) {
        DS_sync(0);
        i = 0;
        n = DsSyncIndex_;
        do {
            if (DsSyncQ_[n].active == id) {
                n = DS_SYNC_FINISHED;
                goto after_search;
            }
            if (++n >= 8) {
                n = 0;
            }
        } while (++i < 8);
        n = 0;
        if (id < DsSyncQ_[DsSyncIndex_].active) {
            n = DS_SYNC_FINISHED;
        }
after_search:
        if (n != DS_SYNC_FINISHED) {
            return 0;
        }
        n = DsSyncIndex_ - 1;
        if (n < 0) {
            n = 7;
        }
        j = 0;
        if (id != 0) {
            do {
                if (DsSyncQ_[n].active == id) {
                    goto found;
                }
                if (--n < 0) {
                    n = 7;
                }
            } while (++j < 8);
            p = 0;
            goto done;
        } else {
            p = 0;
            if (DsSyncQ_[n].active != 0) {
                goto found;
            }
            goto done;
        }
    } else {
        n = DsSyncIndex_ - 1;
        if (n < 0) {
            n = 7;
        }
        p = 0;
        if (DsSyncQ_[n].active != 0) {
            goto found;
        }
        goto done;
    }
found:
    DsSyncOut_.active = DsSyncQ_[n].active;
    DsSyncOut_.w4 = DsSyncQ_[n].w4;
    DsSyncOut_.w8 = DsSyncQ_[n].w8;
    DsSyncOut_.wC = DsSyncQ_[n].wC;
    p = &DsSyncOut_;
done:
    if (p != 0) {
        cmd = (DsSyncCmd *)p;
        rescpy(result, cmd->param);
        return cmd->command;
    }
    return DS_SYNC_NORESULT;
}
#endif
