# libmcrd_1::func_00000580 — human decision needed

- **Parked:** 2026-10-28T16:56:51.306Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libmcrd/1-libmcrd/func_00000580.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** attempt is itself an INCLUDE_ASM stub; nothing to preserve

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libmcrd_1::func_00000580 verdict STUB — the source still hands the function to the assembler.
No C has been written for it yet, so there is no candidate program, no word count and no residual.
Write the function body. Every number below the verdict starts existing once you do.
```

## Preserved attempt

```c
INCLUDE_ASM("build/libraries/nonmatchings/libmcrd_1", func_00000580);
```
