# libcd_16::func_000009C0 — human decision needed

- **Parked:** 2026-10-20T00:22:27.394Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libcd/16-c_011/func_000009C0.c` (image stub restored; library TU retained)
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
Oracle: libcd_16::func_000009C0 verdict MISMATCH — 564/700 words (80.57%).
Residual (steer by this, not the word count): control-flow 1, population 0, schedule 11, allocation 14.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 0 (0x948) — population 0, schedule 1, allocation 0. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 27 distinct measurements since the residual last improved on [0, 1, 11, 14]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 27 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"

extern volatile u8 *LD_00000B88 asm("$LD_00000B88");
extern volatile u32 *LD_00000BA0 asm("$LD_00000BA0");
extern volatile u32 *LD_00000BA4 asm("$LD_00000BA4");
extern int printf(const char *, ...);

void func_000009C0(s32 arg0, void *arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, s32 arg6) {
    volatile u32 *p;
    volatile u32 dummy;
    s32 i;
    s32 flag;
    u8 val;
    volatile u8 *q;
    s32 limit;

    flag = (u8)arg5;
    limit = 0x10000;
    i = 0;
    while (*(volatile u32 *)(0x1F801088 + (arg0 << 4)) & 0x01000000) {
        if (i == limit) {
            printf("DMA STATUS ERROR %x\n", *(volatile u32 *)(0x1F801088 + (arg0 << 4)));
            break;
        }
        i++;
    }
    if (flag == 1) {
        q = (volatile u8 *)LD_00000BA4;
        val = q[2] | (1 << arg0);
    } else {
        q = (volatile u8 *)LD_00000BA4;
        val = q[2] & ~(1 << arg0);
    }
    q[2] = val;
    dummy = LD_00000BA4[0];
    *(u32 *)LD_00000BA0 |= 1 << ((arg0 << 2) + 3);
    p = (volatile u32 *)(0x1F801080 + (arg0 << 4));
    *p++ = (u32)arg1;
    *p++ = ((u32)arg2 << 16) | (u32)arg3;
    while (!(*LD_00000B88 & 0x40)) {
    }
    *p = arg4;
    dummy = *p;
}
```
