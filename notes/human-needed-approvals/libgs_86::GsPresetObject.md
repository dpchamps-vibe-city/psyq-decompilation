# libgs_86::GsPresetObject — human decision needed

- **Parked:** 2026-10-24T17:01:06.000Z (operator instruction)
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgs/86-preset_2/GsPresetObject.c` (image stub restored;
  library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current
  complete TU, including neighboring functions/data

## What the loop needs

The function is reconstructed from the original words and its structure is now measured,
but the ladder did not reach byte identity. It needs either a new structural hypothesis
(the source's per-group tail sharing and the u_char width of the carried type/gradient
state are the two open items) or a policy decision the ladder cannot make on its own. The
preserved attempt and the oracle report below are the starting point.

## What the preserved attempt establishes (re-derived, not inherited)

- Signature and data contract come from the vendored header, not from inference:
  `u_long *GsPresetObject(GsDOBJ5 *objp, u_long *base_addr)`.
  `objp->tmd` is a `struct TMD_STRUCT *` (mapped by `GsMapModelingData`); the function reads
  `primtop` (offset 0x10) and `primn` (offset 0x14), writes `objp->packet` (offset 0xC),
  and returns the end of the preset area.
- The dispatch is `switch (type & 0xFD)` on the primitive's byte 3 (`cd`), range
  `0x20..0x3D`, default printing `"GPU CODE %02xH not assigned.\n"` (string confirmed in
  the original `.rdata`, jump table at `.rdata+0x20`).
- Each group of consecutive prims with the same code and `GsTMDFlagGRD` (bit 2 of the
  word at `prim+2`) gets a two-word header: `(type<<24) | (next & 0xFFFFFF) |
  (grd ? 0x10000000 : 0)` and the prim count; data starts 3 words later.
- Case bodies and their exact store/advance sequences were transcribed from the original
  words, and the switch-case emission order was recovered from the original block layout
  (0x20, 0x21, 0x24, 0x30, 0x34, 0x28, 0x29, 0x2C, 0x38, 0x3C, 0x31, 0x25, 0x35, 0x39,
  0x2D, 0x3D). Reordering the live switch into that order moved the objective from
  396/477 to 478/539 words, so that order is corroborated by measurement.

## Open residual (steer by this, not the word count)

- `words 486/543`, `cfg 1`, `pop 226`, `sched 15`, allocation ungraded (65/57 unpaired
  value webs). Candidate `.text` 2307 bytes vs original 2387.
- Population deltas: original-only `11x addiu r,r,8`, `6x sw r,0(r)`, `3x lw r,0(r)`,
  `2x andi r,r,0xFF`, `2x addiu r,r,4`, `move`; candidate-only `2x sw r,4(r)`,
  `addiu r,r,28`, one extra `.rdata` relocation. Net: candidate carries 142 stores /
  153 loads, original 146 / 157.
- Two named next hypotheses:
  1. The carried "previous type" / "previous gradient" state must be `u_char`-width so
     the `(old & 0xFF)` masks at the loop head and at the tail survive (they are folded
     away in the preserved attempt because the values' range is provable there).
  2. The per-group tail sharing differs: the original merges only three tails
     (`p += 2`, `p += 1`, `p += 5` variants); the preserved attempt merges five, which
     removes stores the original keeps.

## Policy findings

- none recorded (no raw assembly, no register pinning, no flag override was needed)

## Oracle report for the preserved attempt

```
Oracle: libgs_86::GsPresetObject verdict MISMATCH.
`psx_residual_objective`: words 486/543, cfg 1, pop 226, sched 15, allocation ungraded.
`psx_reverse_pipeline`: residual owner expand/cse/gcse/loop/combine — the two programs do
not contain the same instructions, so every allocation/scheduling reading is provisional.
DEGRADED: target has 40 basic blocks, candidate has 41.
```

## Preserved attempt

See the disabled `#if 0` block in `src/libraries/libgs/86-preset_2/GsPresetObject.c`.
