# libgs signed-division check: compiler-fidelity gap

Date: 2026-10-22. Function: `libgs_24::func_00000268` (first libgs function with a
signed integer division attempted this session).

## The blocker, in one line

The original's signed-division expansion emits the **full** MIPS overflow/
divide-by-zero check (`div` → `bnez divisor / break 7` → `bne divisor,-1 /
bne dividend,INT_MIN / break 6` → `mflo`, checks **before** `mflo`). None of the
three vendored compilers reproduce this sequence under any flag or -O level
tested. So the function (and likely every other libgs function with a signed
division) cannot be byte-matched with the current toolchain.

## Target sequence (build/libraries/nonmatchings/libgs_24/func_00000268.s, ground truth)

```
sll   $4,$4,14            # $4 = VWD0 << 14  (dividend)
div   $0,$4,$2            # $2 = HWD0       (divisor)
bnez  $2, +mflo           # divisor != 0 -> skip
break 7                   #   else divide-by-zero trap
addiu $1,$0,-0x1
bne   $2,$1, +mflo        # divisor != -1  -> skip
        lui $1,(0x80000000>>16)   [delay slot]
bne   $4,$1, +mflo        # dividend != INT_MIN -> skip
break 6                   #   else overflow trap
mflo  $4                  # quotient
```

Both `break 7` and `break 6` are present, and the checks precede `mflo`.

## What each vendored compiler actually emits

Compiled the exact real preprocessed TU
(`build/pipelineReversal/libgs_24::func_00000268/objective/measurement-SUqp1n/
v1/candidate/libgs_24::func_00000268.i`) and a minimal `long g(long x,long y){return x/y;}`
probe through all three compilers, -O0..-O3, plus -ftrapv/-fno-fpe-exceptions/-fwrapv/-fno-peephole/
-fno-inline-functions/-mips2 sweeps:

| compiler         | result for the division                         |
|------------------|-------------------------------------------------|
| trunk-19970318 (production cc1) | bare `div`, **no check, ever**; CSEs operands (defers the HWD0/VWD0 stores) |
| gcc-2.7.2-psx    | bare `div`, no check                             |
| gcc-2.95.2-psx   | `div; mflo; bne divisor,0; break 7` — check **after** mflo, **no** break 6 |

The target is a fourth layout (check before mflo, both breaks) that no vendored
compiler produces.

## Why this is a fidelity gap, not a source spelling

- The check is standard compiler output for signed division, not something a
  clean-C body controls. Every C spelling I tried compiles to a bare `div`
  under the production compiler.
- All three `mips.md` `divsi3` patterns carry the stale comment
  `;; various tests for dividing by 0 and such` while emitting only `div` —
  i.e. the check was *removed* from the backend in all three. The original libgs
  predates that removal (built with a GCC that still expanded the full check).
- The four already-matched libgs_24 functions (GsInitGraph, GsInitGraph2,
  GsSortClear, func_000000E4) contain **no** division (div=0 in each original),
  so the fidelity gap was invisible to them and the compiler was still
  identified as trunk-19970318.

## Affected scope (originals containing a real `div` in libgs)

GsSortBg (libgs_0), GsSortFastBg (libgs_1), GsSortFixBg16 (libgs_2),
func_00000268 (libgs_24), GsSortFixBg32 (libgs_4), GsSetFlatLight (libgs_55),
GsSetRefView2 (libgs_78), GsSetRefView2L (libgs_84).
(libhmd_* `break`s are hardware-debug/draw traps, unrelated.)

## Open / conditional

- This is an impossibility **given the three vendored compilers**. If the project
  can obtain the compiler snapshot the original libgs was actually built with
  (the one that still emitted the full division check), the blocker lifts and the
  function is a normal decompilation (the surrounding matrix/OT/clip code is
  ordinary).
- 2.95.2 is the closest (emits a partial check) but its layout and the register
  allocation/schedule of the whole function differ, so it does not match either.

---

## CORRECTION (2026-10-22, later session) — the "blocker" premise was wrong

The target I analyzed (build/libraries/nonmatchings/libgs_24/func_00000268.s,
507 lines, dated 2026-10-21, containing `div; break7; break6`) is a **STALE
disassembly**. The authoritative current original objects (build/libraries/
originals/libgs_24/*.o, dated 2026-10-22) contain **no break and no div**.

Decisive cross-check: `libgs_4::GsSortFixBg32` is byte-verified EXACT. Its
CURRENT original object (originals/libgs_4/c742d0a4….o) has break6=0, break7=0,
and no opcode-0x0D instruction — yet nonmatchings/libgs_4/GsSortFixBg32.s shows
`div; break7; break6`. A byte-exact match is only possible if the real target
bytes carry no check; therefore the nonmatchings *.s files (old compiler, with
division checks) do not describe the current binary. The current binary was
built with the check-less compiler (matching trunk-19970318), and its division
expands to bare `div`/`rem` with no check.

Consequences:
- The "no compiler can emit the check" observation is still literally true for
  trunk-19970318, but it is IRRELEVANT: the real target has no check.
- The function is NOT blocked by a compiler-fidelity gap. It is blocked by
  **stale target data**: the per-function nonmatchings *.s (10-21) and the
  current original *.o (10-22) disagree, and the current libgs_24 .o does not
  even contain func_00000268 (only GsInitGraph, GsInitGraph2, GsSortClear).
- NEXT: re-derive the authoritative per-function target for libgs_24 from the
  current binary (psx_disassemble_project --all) and re-examine whether
  func_00000268 exists and whether it contains a division at all.
