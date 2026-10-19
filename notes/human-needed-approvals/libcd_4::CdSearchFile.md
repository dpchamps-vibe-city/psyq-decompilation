# libcd_4::CdSearchFile — human decision needed

- **Parked:** 2026-10-19T21:40:11.905Z
- **Reason:** asm-needs-human-approval
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libcd/4-iso9660/CdSearchFile.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** attempt is itself an INCLUDE_ASM stub; nothing to preserve

## What the loop needs

The top escalation tier proposed a source construct the clean-source policy forbids,
and there is no higher agent to adjudicate it. Decide whether the construct is the
correct answer for this function. If it is, add the allowlist entry to
`.pi/autoloop.json` under `sourcePolicy.allowlist` and re-run the loop on this
target. If it is not, the function needs a different structural hypothesis.

## Policy findings

- `configs/flag_overrides.mk:29` — **flag-override** — New per-function compiler flag overrides are forbidden
  `CC1FLAGS_libcd_4 := -fsigned-char`

## Oracle report for the preserved attempt

```
top tier proposed a forbidden construct with no higher tier to adjudicate it
```

## Preserved attempt

```c
INCLUDE_ASM("build/libraries/nonmatchings/libcd_4", CdSearchFile);
```
