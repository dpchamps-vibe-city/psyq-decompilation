# libds_1::DsCommand — human decision needed

- **Parked:** 2026-10-20T21:51:02.910Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libds/1-dssys_2/DsCommand.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** attempt is itself an INCLUDE_ASM stub; nothing to preserve; src/libraries/libds/1-dssys_2/func_00000088.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libds_1::DsCommand.func_00000088.c.2026-10-20T21-51-02-910Z.parked.c; src/libraries/libds/1-dssys_2/func_000004EC.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libds_1::DsCommand.func_000004EC.c.2026-10-20T21-51-02-910Z.parked.c; src/libraries/libds/1-dssys_2/DsInit.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libds_1::DsCommand.DsInit.c.2026-10-20T21-51-02-910Z.parked.c

## Recovery of the interrupted park

The final loop run left this park uncommitted. `DsCommand.c` remains the
original `INCLUDE_ASM`; there is no recovered C candidate and no new policy
exception is requested by this cleanup.

- Restored `DsInit.c`, `func_00000088.c`, and `func_000004EC.c` to their
  committed matching sources, removing the redundant disabled copies appended
  by parking. Their attempted versions remain in the archives listed above.
- Removed the unused experimental `include/library/ds_cmd_inline.h`; no source
  included it. Its contents are preserved at
  `run_output/autoloop/attempts/libds_1::DsCommand.ds_cmd_inline.h.2026-10-20T21-51-02-910Z.parked.h`.
- The complete native `libds_1` object, including all neighbouring functions and
  data, passes the byte-identity oracle with the park in place.

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libds_1::DsCommand verdict STUB — the source still hands the function to the assembler.
No C has been written for it yet, so there is no candidate program, no word count and no residual.
Write the function body. Every number below the verdict starts existing once you do.
```

## Preserved attempt

```c
INCLUDE_ASM("build/libraries/nonmatchings/libds_1", DsCommand);
```
