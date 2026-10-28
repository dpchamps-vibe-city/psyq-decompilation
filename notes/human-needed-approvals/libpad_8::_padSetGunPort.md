# libpad_8::_padSetGunPort — human decision needed

- **Parked:** 2026-10-28T19:48:56.446Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libpad/8-pdgunres/_padSetGunPort.c` (image stub restored; library TU retained)
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
Oracle: libpad_8::_padSetGunPort verdict MISMATCH — 78/308 words (25.32%).
Instruction count delta versus target: -4.
Residual (steer by this, not the word count): control-flow 0, population 14, schedule 5, allocation 26.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 0 (0x150) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 11 distinct measurements since the residual last improved on [0, 10, 5, 26]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 11 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include "libpad-internal.h"

extern PadInfo2 *_padInfoDir;
extern u8 _padGunEnalePort;
extern u8 D_00000568;
extern u8 D_00000569;
extern u8 D_0000056A;
extern s32 D_00000558;
extern s32 D_0000055C;
extern s32 B_00000570;
extern u8 B_00000578[8];

PadInfo2 *_padGunSavePadPtr[2];
u8 *_padGunSaveTxBuf[2];
s32 _padGunSaveTxLen[2];

void _padSetGunPort(void) {
    PadInfo2 *pad;
    u32 bit;
    u32 enable;
    u32 mask;
    int mtap;
    u8 *row;
    u8 *cntp;
    u8 *cmdp;
    int i;
    int j;

    if (_padGunSavePadPtr[0] != 0) {
        _padGunSavePadPtr[0]->actTable = _padGunSaveTxBuf[0];
        _padGunSavePadPtr[0]->actSize = _padGunSaveTxLen[0];
        _padGunSavePadPtr[0] = 0;
        _padGunSaveTxBuf[0] = 0;
    }
    if (_padGunSavePadPtr[1] != 0) {
        _padGunSavePadPtr[1]->actTable = _padGunSaveTxBuf[1];
        _padGunSavePadPtr[1]->actSize = _padGunSaveTxLen[1];
        _padGunSavePadPtr[1] = 0;
        _padGunSaveTxBuf[1] = 0;
    }

    mask = 0;
    for (i = 0; i < 2; i++) {
        if (_padInfoDir[i].mtapType == 8) {
            pad = _padInfoDir[i].child;
            for (j = 0; j < 4; j++) {
                if (pad->mtapType == 3) {
                    mask |= 1 << (j + i * 4);
                }
                pad++;
            }
        } else if (_padInfoDir[i].mtapType == 3) {
            if (i != 0) {
                mask = (mask & 0xFF) | 0x10;
            } else {
                mask = (mask & 0xFF) | 0x01;
            }
        }
    }

    enable = mask & _padGunEnalePort;
    if (enable != (D_00000568 & D_00000569)) {
        B_00000570 = 0;
        bit = 1;
        for (i = 0; i < 2; i++) {
            row = &B_00000578[i * 4];
            for (j = 0; j < 4; j++) {
                if (enable & bit) {
                    u8 cnt = B_00000570;
                    if (_padInfoDir[i].mtapType == 8) {
                        cnt++;
                    }
                    row[j] = cnt;
                    B_00000570++;
                }
                bit <<= 1;
            }
        }
        D_00000568 = mask;
        D_00000569 = _padGunEnalePort;
    }

    mtap = 8;
    cntp = (u8 *)&B_00000570;
    bit = 1;
    row = B_00000578;
    cmdp = &D_0000056A;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (enable & bit) {
                if (row[j] == 0) {
                    if (_padInfoDir[i].mtapType == mtap) {
                        pad = (i ? &_padInfoDir[1] : &_padInfoDir[0])->child + j;
                        _padGunSavePadPtr[i] = pad;
                        D_0000055C = i * 16 + j;
                    } else {
                        pad = i ? &_padInfoDir[1] : &_padInfoDir[0];
                        _padGunSavePadPtr[i] = pad;
                        D_00000558 = i * 16 + j;
                    }
                    row[j] = *cntp - 1;
                    _padGunSaveTxBuf[i] = pad->actTable;
                    _padGunSaveTxLen[i] = pad->actSize;
                    pad->actTable = cmdp;
                    pad->actSize = 1;
                } else {
                    row[j]--;
                }
            }
            bit <<= 1;
        }
        row += 4;
    }
}
```
