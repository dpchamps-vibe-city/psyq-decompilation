INCLUDE_ASM("build/libraries/nonmatchings/libpad_19", _padLoadActInfo);


/* PARKED by /auto_decompilation_loop on 2026-10-28T23:09:17.424Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libpad_19::_padLoadActInfo.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"

void func_00001004(PadInfo2 *);
s32 func_000010AC(PadInfo2 *);

s32 _padLoadActInfo(PadInfo2 *arg0, u8 *arg1) {
    s32 temp_a1;
    u8 *temp_a1_2;

    if (arg1 == NULL) {
        goto rejected;
    }
    if (arg0->actAlignData != NULL) {
        return 0;
    }
    if (_padFuncChkEng(arg0) == 0) {
        goto initialize;
    }
rejected:
    return 0;
initialize:
            arg0->state = 4;
            arg0->commandState = 1;
            arg0->prepareCommand = func_00001004;
            arg0->applyResponse = func_000010AC;
            temp_a1 = ((s32) (arg1 + 3) >> 2) * 4;
            arg0->idTable = (u16 *) temp_a1;
            arg0->pad47[0] = 0;
            temp_a1_2 = (u8 *)(temp_a1 + (((s32) (arg0->idCount + 1) >> 1) * 4));
            arg0->actAlignData = temp_a1_2;
            arg0->combTable = &temp_a1_2[((arg0->actAlignCount * 5) + 3) & 0xFFC];
    return 1;
}
#endif
