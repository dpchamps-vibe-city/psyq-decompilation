# Hand-written assembly members: how they were split out, translated, verified and annotated

Record of the process run on 2026-10-15. Everything below is reproducible from
the scripts named; the numbers are the state at the end of that day.

| Result | Count |
|---|---|
| members reconstructed as one-file assembly TUs | 625 of 2,224 |
| functions in them | 668 of 3,201 |
| code bytes | 274,784 of 1,243,796 |
| by library | libgte 371 fn, libhmd 263, libapi 8, libgun 6, libcard 5, libmcx 5, libpad 4, libpress 4, libc2 2 |
| `npm run check-all` | all 2,224 members byte-exact |
| annotated (semantic comments, named labels) | 16 (the RotSMD family) |

## 1. Classification: which members were written in assembly

Each original object was classed from its bytes, per function, then per member
(`notes/research/asmify/asm_members.json` lists the result; the scratch census
that produced it is summarised here because its rules matter more than its code).

Function classes:

- **hard-asm**: carries an instruction pattern GCC 2.7.2 never emits. The
  markers, with the members they occur in: `$at` used as a scratch register
  (313), a GTE command preceded by exactly one hazard nop where the SDK's C
  macros emit two or none and gas adds none (506), a callee-saved register
  written without being saved (45), `$ra` or `$sp` loaded from a buffer (19),
  syscall/coprocessor-0/break (9), a jump through a register other than `$ra`
  (5). 592 of the 625 carry at least one.
- **C-frame**: GCC's prologue/epilogue and register discipline.
- **GTE C-macro shape**: a C-frame function whose only non-C instructions are
  GTE commands spaced by the SDK macro convention (`nop; nop; cop2`).
- **GTE leaf, undecided**: resolved per member by the nop convention (0 or 1
  nop before GTE commands = hand, 2 = SDK macro) and by family.

Member form: a member with a hard-asm function and no C-frame or macro-shaped
function is an **assembly file**; one with macro-shaped functions is **C with
SDK GTE macros** (175 members, 433 functions, all of libgs and the libgte/libhmd
helpers); BIOS thunks and plain C are the rest. No member mixes a C-shaped and
an assembly-evident function.

Cross-checks that make the boundary credible:

- the split follows Sony's product families, not GTE use: in libhmd the basic
  polygon drivers (unit-type prefixes 0000, 0002, 0004, 0010, 0014, 0020, 0024,
  0030, 0034, 01xx) are assembly and the later families (0001/0003/0005, 0200,
  0300, 0301, 04xx-07xx, MIMe, animation) are C; in libgte every polygon-driver
  family is assembly and every register accessor, divide, clip and math family
  is C; only mtx (13/9) and smp (30/3) are mixed;
- the 650 libgte/libhmd functions classed as C contain zero uses of `$at`;
- Sony shipped the assembler workflow itself: `INLINE_A.H` ("Macro definitions
  of DMPSX version 3 for Assembler programs") beside `INLINE_C.H`.

The 33 members without a hard marker are GTE leaves: 26 sit in families whose
siblings carry markers (libgte smp 10, libhmd block 0114 8, msc06 4, mtx 3,
nom 1); the thin singletons are the four trr members, hgt, msc05 and mime_s.
If one of them ever matches as C, the TU form switches and the comments move
into the C.

The harness scanner (`npm run scan-handwritten`, `docs/handwritten-assembly.md`
in the harness) is a narrower, advisory view: it nominates 12 high-confidence
functions. `notes/research/handwritten-assembly-candidates.md` discusses those.

## 2. Translation: disassembly to natural gas source

`notes/research/asmify/asmify.py` (run from the project root) reads
`build/libraries/disassembly/<member>/member.s` for each listed member and
writes `build/asmify/out/<lib>/<tu>/<name>.s`: `li`/`la`/`lw reg,sym` forms,
`.L` labels, GTE mnemonics, no disassembler artifacts. Two source forms are
tried and the one that reproduces the bytes is kept:

- **reorder** (41 members: libapi 6, libcard 2, libmcx 1, libpad 1, 31 small
  libgte leaves): nops dropped, gas re-derives hazards and fills delay slots;
- **whole-file `.set noreorder`** (584: all libhmd, most libgte): explicit nops,
  because the bytes contain empty delay slots gas would have filled, labels on
  hazard nops, and back-to-back `mtc2` with no nop between.

Assembler facts the forms depend on (GNU as 2.42, `-march=r3000`): a nop is
inserted after every `mtc2`/`ctc2` and between `mfc2` and a use of its result;
no nop is inserted between `lwc2` and a cop2 command; `move` encodes as `or`.
The production `move`-to-`addu` rewrite applies to `.s` parts as to compiler
output. libpress keeps explicit `or rd,rs,$zero` because its originals are
or-encoded moves.

## 3. Oracle: folding same-object references

Converted PSY-Q objects patch a reference to a global defined in the same file
as section + offset; GNU as keeps the symbol. Both link to identical bytes. The
harness oracle (`canonicalizeDefinedReferences` in
`tools/lib/relocatableObject.ts`) now folds the two forms symmetrically before
its strict comparison. 14 assembly members need it (libcard patch/end, libpad
pdhokres, libgun newgun, libgte divXXa, patchgte, libmcx mcxdsr). The same
fold unblocks 74 C members (libc qsort, libcd c_011, libc2 putchar, libapi
i_heap3, ...) that could never have matched before; none had a record.

## 4. Install: one `.s` per original object

`notes/research/asmify/import.py` copies each output to
`src/libraries/<lib>/<ordinal>-<name>/<name>.s`, deletes the stub and shared
header parts, and rewrites `tu.json` to the one-part form
`{ "parts": [{ "path": "<name>.s", "symbols": [...] }] }`. It is idempotent and
refuses to replace real C except where listed: libapi/74-patch held two matched
C thunks (`EnablePAD`, `DisablePAD`, commit f885794) beside the hand-written
`_patch_pad`; since one object is one source, the whole member is the `.s`.

Member names such as `108-smd_00` are Sony's object names from the `.LIB`
tables (`library-input/redux/original-members.json`) and are the only trace of
the original source layout; they stay.

## 5. Verification and reporting

- `npm run library -- check --member ID` re-verifies the member (and every
  accepted member, about 12 s); `npm run check-all` verifies all 2,224.
  `npm run check -- --member` is not accepted by the npm wrapper.
- verified records carry `form: "assembly"`; `npm run progress` reports
  `MATCH-ASM` separately from `MATCH-C`; `npm run graph` entries carry
  `sourceForm: "assembly"` and `decompiled: true`, so the C agent queue excludes
  them (2,346 functions remain in it).
- the harness inspects a `.s` part before assembling: backlog markers,
  `.reloc`, `.incbin` and path includes are rejected; only `.include "name.inc"`
  resolved from the configured include directories is allowed.

## 6. Annotation: making the files intelligible

Comments, `.L` label names and local data labels are invisible to the oracle,
so every annotation step ends with a re-verification and nothing else.

Conventions (settled with the user on 2026-10-15):

- **GTE spelling** follows Sony's `INLINE_A.H` via `include/inline_a.inc`:
  `RTPT`, `NCLIP`, `AVSZ3`, `MVMVA sf,mx,v,cv,lm`, `SQR sf`, ... assembling the
  real cop2 words. The two-nop `n` forms are not reproduced: gas macro names are
  case-insensitive and `nOP` would capture every `nop`. Hazard nops stay written
  out where the bytes place them. The community `include/gte_macros.inc` remains
  for the C-side stubs.
- **Header** (model `src/libraries/libgte/108-smd_00/smd_00.s`): original
  library and object, SDK prototype of every function, a purpose paragraph, a
  `Register use:` table. `notes/research/asmify/annotate.py` generated the
  mechanical part for all 625: prototypes for 510 of 668 functions (419 full
  declarations, 64 K&R lists from libgs.h, 27 from commented-out blocks), the
  argument registers and entry stack offsets, and for `GsU_` drivers the unit
  type decoded from `libhmd.h`. The 158 without a declaration are mostly the
  undocumented `GsTMDfast*B/D/M`, `GsPrst*D` drivers and private routines.
- **Labels** are role names: `.Lnext`, `.Lclip_v1`, `.Laccept`, `.Lreject`,
  `.Ldone`.
- **Family notes** live in `notes/file-groupings.md`:
  `notes/research/asmify/groupings.py` generated 117 sections (63 families of
  three or more covering 571 members, the rest singletons) in the ledger
  parser's convention, each with objects, targets, shared instruction structure,
  hand-written evidence, verification and an Annotation line. Regenerate by
  replacing everything below the marker comment.
- **Per-family semantic pass**: `notes/research/asmify/families/smd.py` is the
  model. The RotSMD family's 16 members are four instruction-stream classes
  (triangle, quad, shared-vertex triangle, shared-vertex quad); each class has
  one purpose paragraph, one register table, one label map and one comment map
  keyed by instruction index, asserted against the mnemonic before writing.
  Across all families: smd/rmd collapse to 4 skeletons of 16 and nmd/pmd to 8;
  every other family (libhmd blocks, cmb, nom, tmd, the 4-member polygon
  families) is edited copies at 60-90 percent similarity, so comments carry but
  must be re-placed.

Remaining naming work: 19 `func_` private routines (10 files, mostly the libgte
divXXa helpers), 67 `D_/B_/T_` local data labels (25 files), one file with raw
`.sbss` offsets (libgun newgun). All are local symbols; renaming is free.

The automation of the per-family pass is `plans/assembly-annotation-mode.md`.

## 7. Repeating or extending the process

```
python3 notes/research/asmify/asmify.py                 # translate (build/asmify/out)
python3 notes/research/asmify/import.py                 # install as assembly TUs
python3 notes/research/asmify/annotate.py               # spelling + mechanical headers
python3 notes/research/asmify/groupings.py > /tmp/g.md  # family sections (paste below the marker)
npm run check-all                                       # every member byte-exact
npm run graph && npm run progress                       # queue and counts
```

A newly classed member goes into `asm_members.json`, then through the same
four scripts. A member later shown to be C is reverted with `git checkout` of
its TU directory; the oracle decides, the classification never does.
