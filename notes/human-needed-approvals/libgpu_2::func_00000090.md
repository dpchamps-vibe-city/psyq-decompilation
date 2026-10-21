# libgpu_2::func_00000090 — human decision needed

- **Parked:** 2026-10-21T13:18:47.816Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgpu/2-kprintf/func_00000090.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** src/libraries/libgpu/2-kprintf/_shared-0.h: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libgpu_2::func_00000090._shared-0.h.2026-10-21T13-18-47-816Z.parked.c

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libgpu_2::func_00000090 verdict MISMATCH — 47/960 words (4.9%).
Residual (steer by this, not the word count): control-flow 21, population 146, schedule 2, allocation 5.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 0 (0x8) — population 3, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 164 distinct measurements since the residual last improved on [0, 0, 1, 6]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 164 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <libapi.h>
#include <memory.h>
#include <stdio.h>

s32 hankanjitrans();
s32 kanjitrans(s32);
extern u8 B_0000B8B0;
extern s32 D_00001068;
extern u8 txyuv;
extern char RO_STR_00000F90[];

s32 func_00000090(s8 *arg0) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s1;
    s32 var_s0;
    s32 var_v0_2;
    u32 var_a0;

    if ((u32) (((u8) arg0[0] + 0x7F) & 0xFF) >= 0x18U) {
        var_s0 = hankanjitrans(*(volatile u8 *) arg0);
        if (!(var_s0 & 0xFFFF)) {
            return -1;
        }
        goto block_4;
    }
    var_s0 = ((u8) arg0[1]) | (*(volatile u8 *) arg0 << 8);
block_4:
    var_a0 = 0x8140;
    if ((u32) ((var_s0 + 0x7EC0) & 0xFFFF) >= 0x37FU) {
        var_a0 = 0x889F;
        if ((u32) ((var_s0 + 0x7761) & 0xFFFF) >= 0xFD4U) {
            printf(RO_STR_00000F90, var_s0 & 0xFFFF);
            return -1;
        }
    }
    temp_s1 = Krom2RawAdd(var_a0);
    bcopy((u8 *) (temp_s1 + (kanjitrans(var_s0 & 0xFFFF) * 0x1E)), (&B_0000B8B0 + (D_00001068 << 5)), 0x1E);
    var_v0_2 = D_00001068;
    temp_a1 = D_00001068 * 0x10;
    if (D_00001068 < 0) {
        var_v0_2 = D_00001068 + 0xF;
    }
    temp_a0 = (var_v0_2 >> 4) * 0x10;
    *((s32 *) ((u8 *) ((void *) ((u8 *) &txyuv + 8)) + temp_a1)) = (D_00001068 - temp_a0) * 0x10;
    *((s32 *) ((u8 *) ((void *) ((u8 *) &txyuv + 0xC)) + temp_a1)) = temp_a0;
    return 0;
}
```
