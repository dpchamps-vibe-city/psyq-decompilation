# libcd_44::func_000003F0 — human decision needed

- **Parked:** 2026-10-20T16:51:24.833Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libcd/44-cdr_1/func_000003F0.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** src/libraries/libcd/44-cdr_1/func_000000AC.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libcd_44::func_000003F0.func_000000AC.c.2026-10-20T16-51-24-833Z.parked.c

## Recovery verification

A later full-project check exposed a packaging failure despite all 616
instruction words matching: the rebuilt native object had an extra undefined
`func_00000078` symbol (first differing `.OBJ` record #29). The compiled callback
used `$Lfunc_00000078`, but retained assembly referenced the unprefixed name.

The split generator's `sourceReferences` scans the TU's manifest parts, not
headers included by those parts. The callback's explicit asm-name declaration
was hidden in `cdr1_private_head.h`, while its C identifier appeared in the TU
parts. Moving that existing declaration into `func_000000AC.c` makes it visible
to both the compiler and split generator. Regenerated assembly now references
`$Lfunc_00000078` consistently; no assembly, flags, or target bytes were edited.

The redundant disabled neighbour copy was removed from `func_000000AC.c`;
its parked archive listed above remains available. `func_000003F0` itself stays
parked on its original extraction. `npm run diff -- libcd_44::func_000000AC`
now verifies the complete native object, including symbols and relocations,
not just the selected function's words. After split regeneration,
`npm run check-all` verifies all 2164 configured library members as byte-exact;
the project-wide source-policy check passes for all 348 compiled functions.

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libcd_44::func_000003F0 verdict UNKNOWN — 0/0 words (0%).
Residual (steer by this, not the word count): control-flow 0, population 2, schedule 2, allocation 3.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 15 (0x54C) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 23 distinct measurements since the residual last improved on [0, 2, 2, 3]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 23 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>
#include <stdio.h>

extern s32 CD_read_dma_mode;
extern volatile CdReadState cd __asm__("$LD_00000A68");
extern char CdRead_shell_open[] __asm__("$LRO_STR_00000A18+24");
extern char CdRead_retry[] __asm__("$LRO_STR_00000A18+48");

int func_000003F0(s32 arg0) __asm__("$Lfunc_000003F0");

int func_000003F0(s32 arg0) {
    u8 sp10;
    s32 temp_s0;

    CdSyncCallback(0);
    CdReadyCallback(0);
    if (CD_read_dma_mode & 1) {
        CdDataCallback(0);
    }
    if (CdStatus() & 0x10) {
        if ((VSync(-1) & 0x3F) == 0) {
            puts(CdRead_shell_open);
        }
        CdControlF(1, 0);
        cd.unk1C = VSync(-1);
        cd.unk14 = -1;
        return cd.unk14;
    }
    if (((arg0 != 0) && (puts(CdRead_retry), CdControl(9, 0, 0),
                          (CdControl(2, (u_char *)CdLastPos(), 0) == 0))) ||
        (((CdFlush(), temp_s0 = cd.unkC), sp10 = temp_s0,
          ((temp_s0 & 0xFF) != CdMode())) || (arg0 != 0)) &&
         (CdControl(0xE, &sp10, 0) == 0)) {
        cd.unk14 = -1;
        return cd.unk14;
    }
    cd.unk20 = CdPosToInt(CdLastPos());
    CdReadyCallback(func_000000AC);
    if (CD_read_dma_mode & 1) {
        CdDataCallback(func_00000320);
    }
    cd.unk8 = cd.unk4;
    CdControlF(6, 0);
    cd.unk14 = cd.unk0;
    cd.unk18 = VSync(-1);
    return cd.unk14;
}
```
