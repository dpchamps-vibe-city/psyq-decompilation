# libapi_87::realloc3 — resolved

**Resolved 2026-10-17:** clean C is byte-exact (57/57) and passed the full
finalization gate, identity
`2b232023496cad13043cd7ae57fb0a22ce4c3e0d4b7626e5cb9c554a41ad7230`.
No additional flag override or policy exception was needed. See
[the measured repair](../research/realloc3-cse-loop-boundary.md).
The historical park below is retained for provenance; it is not an outstanding
approval request.

## Historical park

- **Parked:** 2026-10-17T00:52:31.326Z
- **Reason:** asm-needs-human-approval
- **Escalation reached:** deepseek-v4-1-flash
- **Source:** `src/libraries/libapi/87-realloc3/realloc3.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** Library park preserves the complete member TU unchanged; no disabled neighbor bodies or original-object fallback

## What the loop needs

The top escalation tier proposed a source construct the clean-source policy forbids,
and there is no higher agent to adjudicate it. Decide whether the construct is the
correct answer for this function. If it is, add the allowlist entry to
`.pi/autoloop.json` under `sourcePolicy.allowlist` and re-run the loop on this
target. If it is not, the function needs a different structural hypothesis.

## Policy findings

- `configs/flag_overrides.mk:9` — **flag-override** — New per-function compiler flag overrides are forbidden
  `CC1FLAGS_libapi_87 := -fno-cse-follow-jumps -fno-cse-skip-blocks`

## Oracle report for the preserved attempt

```
top tier proposed a forbidden construct with no higher tier to adjudicate it
```

## Preserved attempt

```c
INCLUDE_ASM("build/libraries/nonmatchings/libapi_87", realloc3);
```
