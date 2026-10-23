# libgs_42::GsSetLightMatrix — parked (blocked)

- **Parked:** 2026-10-23T21:53:35.000Z
- **Reason:** blocked (witnessed toolchain/compiler-profile blocker, not a policy question)
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgs/42-matrix5/GsSetLightMatrix.c` (INCLUDE_ASM stub restored; best attempt preserved behind `#if 0`)
- **Target object:** `library-input/redux/libgs/42-matrix5.o` (byte-identical to `library-input/converted/lib/libgs/matrix5.o`)

## What the loop needs

libgs_42 needs a **per-member compiler profile** for libgs. The project's own
research already flags this: `notes/research/compiler-identification-1997-trunk.md`
line 101 states that DCB needed a *second* profile — "a later 2.8-era snapshot,
still text-epilogue, no post-reload CSE" — for part of `libsnd/libcd/libgs/libc2`,
and "**None of those members are in our corpus**". This function is exactly such
an unvalidated libgs member.

With the configured `trunk-19970318-psx` cc1 the function is **one instruction
off** (population 1, schedule 6; best clean-C source is the obvious struct copy).
The gap is the block-move lowering, not a source spelling.

## Witnessed target (37 insns + 3 pad, frame 0x40)

```
addiu sp,-64 ; sw s1,52 ; move s1,a0 ; sw ra,56 ; sw s0,48
lui a1,%hi(GsLIGHTWSMATRIX) ; addiu a1,a1,%lo(...)      ; base in a1, AFTER the saves
lw v0,0(a1)  lw v1,4(a1)  lw a0,8(a1)   sw v0,16 sw v1,20 sw a0,24
lw v0,12(a1) lw v1,16(a1) lw a0,20(a1)  sw v0,28 sw v1,32 sw a0,36
lw v0,24(a1) lw v1,28(a1)               sw v0,40 ; jal PushMatrix
                                                        sw v1,44 (delay slot)
addiu s0,sp,16 ; move a0,s0 ; jal MulMatrix ; move a1,s1
jal PopMatrix ; nop ; jal SetLightMatrix ; move a0,s0
epilogue
```

- The 32-byte copy is emitted as **exactly `output_block_move(num_regs=3)`**: groups
  of 3 loads then 3 stores (3+3+2), i.e. a `movstrsi_internal` whose 4th scratch
  collided with an address register.
- The 6th load `lw a0,20(a1)` is element 5 (`t[0]`); `a0` is stored to `0x24(sp)`
  **and** used as the `PushMatrix` first argument with **no separate load and no
  move** (direct fusion).

## Why the vendored toolchain cannot reach it (measured)

| compiler | frame / mp | copy | `t[0]` arg |
|---|---|---|---|
| trunk-19970318 (production) | 64 / s1 ✓ | 4-wide `movstrsi_internal` | **separate** `lw a0,20(base)` (pop 1) |
| 2.7.2-psx | 64 / s1 ✓ | 4-wide | separate `lw a0,GsLIGHTWSMATRIX+20` (absolute) |
| 2.95.2-psx | 56 / s0 | 8-wide (move_by_pieces) | fused **but** `lw $3,20; move $4,$3` |

- **Trunk**: `emit_block_move` picks `movstrsi_internal` (`MOVE_RATIO = 2` because
  `HAVE_movstrsi`; `expand_block_move` copies both addresses to registers and emits
  one opaque insn). Its 8 loads are produced at assembly output by
  `output_block_move`, invisible to CSE, so the `t[0]` load is never fused. Proven
  with a minimal probe `m=A; g(A.t[0])` → two loads of offset 20.
- **2.95.2** fuses (visible move-by-pieces loads) but with the wrong frame/registers
  and an extra `move`.
- No vendored compiler produces frame-64/mp-s1 **and** 3-wide **and** direct
  fusion simultaneously.

## Direction space closed (see `run_output` closed-directions rows)

- ~25 sources measured: struct copy / direct-init / pointer source / preload t0 /
  member-wise / union / long-array / byte-offset longs / loop / volatile dst,src /
  aliased `t[0]` / reordered `PushMatrix`. Best remains the plain struct copy at
  pop 1, sched 6. Element-wise always collapses to the 8-wide+fused codegen (pop 7).
- `psx_flag_probe`: only scheduling flags move the masked score (8/40 vs 7/40
  baseline); no flag changes the block-move lowering.
- `psx_reconstruct_function`: context-unresolved (ET_REL relocations unsupported).

## Decision

Supply or configure a pinned cc1 for libgs whose 32-byte block move is fusible
(and whose allocator keeps mp→s1/&m→s0), then retry. Otherwise accept this member
as a retained original-object extraction. The preserved `#if 0` attempt is the
correct source under that compiler; only the block-move lowering differs.
