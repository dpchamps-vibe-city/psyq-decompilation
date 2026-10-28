# libpad_19::_padLoadActInfo — human decision needed

- **Parked:** 2026-10-28T23:09:17.424Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libpad/19-pdresres/_padLoadActInfo.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libpad_19::_padLoadActInfo verdict MISMATCH — 1926/1948 words (98.87%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 3, allocation 8.
Next block: 4 (0xF00) — population 0, schedule 3, allocation 7. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.
```

## Preserved attempt

```c
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
```
