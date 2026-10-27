#include "common.h"

extern volatile s32 B_00001B48[];
extern void VSyncCallbacks(s32, void (*)(u8, u8 *, s32 *, s32 *));
extern void _card_stop(void);

void MemCardStop(void)
{
    while (B_00001B48[12] != 0) {
    }
    VSyncCallbacks(7, 0);
    _card_stop();
}


/* PARKED by /auto_decompilation_loop on 2026-10-27T16:33:21.187Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcrd_1::func_000001FC.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"

extern s32 B_00001B78;
extern void VSyncCallbacks(s32, void (*)(u8, u8 *, s32 *, s32 *));
extern void _card_stop(void);

void MemCardStop(void)
{
    while (*(volatile s32 *)&B_00001B78 != 0) {
    }
    VSyncCallbacks(7, 0);
    _card_stop();
}
#endif
