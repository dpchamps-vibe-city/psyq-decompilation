INCLUDE_ASM("build/libraries/nonmatchings/libcd_38", CdControl);


/* PARKED by /auto_decompilation_loop on 2026-10-20T15:58:18.848Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libcd_38::CdControl.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libcd.h>

extern s32 CD_cw(s32 com, u8 *param, u8 *result, s32 mode);
extern void (*CD_cbsync)(u8, u8 *);
extern u8 CD_status;
extern s32 LD_00000430[] asm("$LD_00000430");

int CdControl(u_char com, u_char *param, u_char *result) {
    void (*saved)(u8, u8 *);
    s32 i;
    s32 ret;
    s32 c;
    s32 end;
    s32 *table;
    s32 *base;

    c = com & 0xFF;
    base = LD_00000430;
    saved = CD_cbsync;
    for (i = 3, table = base + c, ret = 0, end = -1; i != end; i--) {
        CD_cbsync = 0;
        if ((c != 1) && (CD_status & 0x10)) {
            CD_cw(1, 0, 0, 0);
        }
        if ((param != 0) && (*table != 0)) {
            if (CD_cw(2, param, result, 0) != 0) {
                continue;
            }
        }
        CD_cbsync = saved;
        if (CD_cw(com, param, result, 0) == 0) {
            goto done;
        }
    }
    CD_cbsync = saved;
    ret = -1;
done:
    return ret + 1;
}
#endif
