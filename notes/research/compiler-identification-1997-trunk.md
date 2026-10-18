# Which compiler built the PSY-Q 4.7 C objects: a 1997 GCC trunk snapshot

Date: 2026-10-17. Scope: identify the compiler behind the C-reconstructed library members and show a migration path for the 137 existing C members. All measurements use the project's own whole-member relocatable-object oracle (`compareRelocatableObjects`), the production GAS stage (`move`→`addu` rewrite), and the production per-TU flags unless a column says otherwise. Nothing in production (`toolchain.json`, flags, sources, verification records) was changed by this work.

## 1. Bottom line

- **Identification.** The library compiler is a GCC *development-trunk* snapshot from the six weeks between **1997-02-05** and **1997-03-18**, built with the MIPS-assembler output mode (no split addresses) and the GCC 2.7.2-era text epilogue. It is not stock 2.7.2, not any 2.7.2.x, and not any released 2.8.x; the SN executables shipped with the SDK are irrelevant to the library objects.
- **Best available artifact.** `cygnus-2.7.2-970404` (the Cygnus "CDK" compiler, source at `ser-pounce/cdk-gcc` tag `b18`) is a trunk snapshot of early April 1997. With two later upstream commits reverted (1997-03-18 `38b610ed8e01` and 1997-03-26 `2a9fb5489fc5`), it reproduces **137 of 137** C corpus members with the existing sources, reproduces the whole `realloc3` member with **all three functions in C** (the byte-copy helper that 2.7.2 and Homebrew 2.8.1 could never produce), lets the two allocator flag overrides be retired, and matches a member outside the corpus (`libc/48-memmove.o`) from ordinary C where 2.7.2 and 2.8.1 fail.
- **A pure FSF trunk snapshot confirms it.** The GCC git tree at commit `2b3600acb4ec` (1997-03-18 18:38 UTC, the last commit before the parameter REG_EQUIV change), built with only build scaffolding borrowed from the CDK tree and run with `-mmips-as -fno-exceptions`, also reproduces 137/137, the all-C `realloc3`, the override-free allocator helpers and `memmove`. The identification therefore does not rest on any Cygnus-local code.
- **Stock CDK as-is** (no source change) in the same output mode reproduces 132/137; its five misses are exactly the two post-window commits acting on `libapi/14-c160`, `73-sc2b`, `75-first`, `76-pad`, `81-realloc2`.
- **Homebrew 2.8.1** is excluded as the library compiler by a whole-SDK census: no Sony member carries a 2.8 RTL epilogue, and its `make_return_insns`/post-reload CSE behavior is absent from the originals.
- **Confirmed on Sony's own source (2026-10-18, section 8).** Replaying Sony's libhmd makefiles over the SDK's disclosed C sources rebuilds 275 of 305 C objects byte for byte as whole files with the pinned `cc1`. That rises to 281 with the documented DMPSX C-macro table. Both window edges are now single commits confirmed by this corpus: `cabcf079ea40` (1997-02-05) and `38b610ed8e01` (1997-03-18). Every sampled snapshot between them behaves identically.

| Compiler (cc1) | Output mode | Exact members / 137 | Fully-C / 121 |
| --- | --- | ---: | ---: |
| GCC 2.7.2-psx (production, sources tuned for it) | `-mgas` | 137 | 121 |
| Homebrew Psy-Q 2.8.1, same flags | `-mgas` (splits) | 115 | 110 |
| Homebrew Psy-Q 2.8.1 | `-mgas -mno-split-addresses` | 124 | 113 |
| cygnus-2.7.2-970404 (stock) | `-mgas` (forced split) | 118 | 112 |
| cygnus-2.7.2-970404 (stock) | `-mmips-as` | 132 | 119 |
| same, post-reload CSE call (1997-03-26) disabled | `-mmips-as` | 134 | 120 |
| same, plus 1997-03-18 parameter REG_EQUIV reverted (**candidate**) | `-mmips-as` | **137** | **121** |
| FSF trunk `2b3600acb4ec` (1997-03-18), scaffolding from CDK | `-mmips-as -fno-exceptions` | **137** | **121** |
| same | `-mmips-as` (that snapshot emits an EH unwinder call per function by default) | 0 | 0 |

`-fno-regmove` (the CDK's Cygnus-local pass) changes nothing in any row.

## 2. Evidence that the producer is not 2.7.2, 2.7.2.x, 2.8.x, or an SN build

Whole-SDK censuses over all 2,224 converted originals (`build/compiler-fit/*.py`):

- **Epilogue shape** (`return-slot-census.py`): every Sony member uses the 2.7.2-era *text* epilogue: multi-register frames `lw ra; lw s*; jr ra; addiu sp` (1,290), RA-only frames `lw ra; addiu sp; jr ra; nop` (301) or `lw ra; <delay insn>; jr ra; addiu sp` (36). The 2.8 RTL-epilogue signature for RA-only frames, `lw ra; nop; jr ra; addiu sp`, occurs 6 times, all in `libsn` (SN-built, excluded). GCC enabled the MIPS RTL epilogue on 1997-07-11, so the producer predates it.
- **Address splitting** (`split-store-census.py`): 1,257 global stores use the assembler-macro form `lui $at; s* X,%lo(sym)($at)`; 0 use a compiler-allocated register. The producer never split addresses.
- **Post-reload CSE** (`split-store-census.py`, plus `libapi/14-c160`, `73-sc2b`, `76-pad` under CDK): the originals re-materialize constants a live register already holds (`li t2,160; jr t2; li t1,160`; `li v0,32` after `li s1,32`). `reload_cse_regs` (1997-03-26) replaces those with register copies, as stock CDK, 2.8.0 and 2.8.1 do.
- **Delay-slot filling from a jump's target** (`jump-fill-census.py`): 141 members contain `j L; <first insn of L>` with the jump redirected past it, including `libapi/86-free3.o` and `87-realloc3.o`. Stock 2.7.2's `fill_simple_delay_slots` cannot fill an unconditional jump from its target (added 1995-12-31). This is the mechanism behind the copy helper's `j .text+0x1a4; move v0,t0` that blocked the previous session.
- **Return instructions**: no frameless Sony function has more than one `jr ra` (the 33 that do are hand-written libgte assembly). The producer never converted end-of-function jumps to returns.
- **Register-parameter allocation** (`libapi/75-first`, `81-realloc2`, `73-sc2b`): parameter copies win the lowest callee-saved register. Upstream commit `38b610ed8e01` (1997-03-18, "Add a REG_EQUIV note when a register parameter has a stack location") adds a `REG_EQUIV (mem)` note to those copies, after which `update_equiv_regs` doubles their `reg_live_length` (verified in the `.lreg` dumps: 15→30, 17→34, 29→58) and `global.c` ranks them below other pseudos, producing the `s0/s1` and `s2/s3` swaps that stock CDK shows.

Independent prior work agrees. The DCB project (same SDK 4.7, `ReGame-Labs/dcb_decomp`, `tools/patch_cc1.py`) matched Psy-Q 4.7 objects only after binary-patching eighteen "GCC 2.8" behaviors into stock 2.7.2. Thirteen of those behaviors are verified present in the Cygnus 970404 source as ordinary upstream code (fill from target, `find_dead_or_set_registers` for both jump paths, `find_best_addr` cost test, `alter_reg` slot alignment, `expand_increment` queue path, lowpart-SUBREG cost, `call_insn_operand` "ri", symmetric `prune_preferences`, the jump.c `x = a; goto l` rewrite, the store-flag `exact_log2` test, the `i2dest` reference-count fix, the `-fforce-mem` extension change), two are subsumed by those, one was dropped by DCB, one (the combine SIGN_EXTEND split) has identical code text in 2.7.2, 970404 and 2.8.1 and could not be located, and one (re-enabling volatile MEMs after combine) is absent from the released 2.8.1 tree as well, so it dates nothing. Tenchu's GS_107 analysis found the same `lw ra; addiu sp; jr; nop` SDK fingerprint, and Armored Core found PsyQ 4.0's SN 2.7.2 build identical to the decompals 2.7.2 build on its game functions, which is why SN's shipped compilers do not explain the library objects.

## 3. Dating the snapshot

Upstream ChangeLog dates (`homebrew-psyq` 2.8.1 tree, `gcc/ChangeLog`, `ChangeLog.10`) for behaviors the originals exhibit (present) or lack (absent):

| Behavior | Upstream date | Originals |
| --- | --- | --- |
| reorg fills an unconditional jump's slot from its target | 1995-12-31 | present |
| `find_dead_or_set_registers` | 1996-01-24 | present (DCB 16) |
| `mips_split_addresses` unconditional when `TARGET_GAS && optimize` | 1996-06-17 … 1997-04-30 | never split, so the build had `TARGET_GAS` off |
| `expand_increment` MEM post-increment queue path | 1996-09-23 | present (DCB 8) |
| jump.c `if (...) { x = a; goto l; } x = b;` | 1996-10-14 | present (DCB 14) |
| `emit_unop_insn` ZERO_EXTEND like SIGN_EXTEND | 1996-12-10 | present (DCB 12) |
| `try_combine` clears `reg_n_refs` of an unmentioned `i2dest` | 1997-01-29 | present (DCB 18) |
| `alter_reg` does not round spill slots to BIGGEST_ALIGNMENT | **1997-02-05** | present (DCB 6) → lower bound |
| REG_EQUIV on register-parameter copies | **1997-03-18** | absent → upper bound |
| `reload_cse_regs` | 1997-03-26 | absent |
| MIPS RTL epilogue, `mips_can_use_return_insn` | 1997-07-11 | absent |

The lower bound rests on DCB's spill-slot observations (`libmcrd MemCardGetDirentry`, `_SsVmKeyOn`); nothing in our 137-member corpus contradicts it. The upper bound is established locally by three members. Two trunk changes between 1997-03-18 and 970404 that remain in the candidate (`find_dummy_reload` earlyclobber and `emit_push_insn` CLOBBER removal, both 1997-03-25) had no visible effect in the corpus.

The split-address point matters for the production flags: a trunk compiler of this window splits addresses whenever `TARGET_GAS` is set, and the originals never split, so Sony's build was configured for the MIPS assembler (`TARGET_MIPS_AS`) while the objects were nevertheless assembled by GNU as (the `$at` macro expansions and the COFF-converted packaging already established that). Passing `-mmips-as` instead of `-mgas` reproduces that mode without a source change; the only textual consequences are `.set volatile`/`.set novolatile` around volatile accesses and `.set nobopt`, which GAS 2.42 accepts silently. The alternative is to backport the fifteen-line 1997-05-01 `-mno-split-addresses` switch (`8acd7d300281`, `5ef37cd33952`) and keep `-mgas`.

## 4. The candidate compiler, reproducibly

`build/compiler-fit/bin/Dockerfile.cdk` builds `ser-pounce/cdk-gcc` tag `b18` (identical to decompals/old-gcc's `gcc-2.7.2-cdk` recipe: ubuntu:focal, i386 static, `-std=gnu89`). Variants:

| Variant | SHA-256 of `cc1` | Change versus the CDK source |
| --- | --- | --- |
| `stock` | `6f11ba7ed072cc737c3d995274d380e2bd27fc1c64c04147d8cc8e89b79f8d3f` | none; byte-identical to the Silent Hill decomp's `gcc-2.7.2-cdk/cc1` |
| `noreloadcse` | `7ac203bbb3a5182fa41ddceb8f692ab9128229bc35532dce3b5a0b83771a4cf3` | `reload1.c`: the `reload_cse_regs (first)` call disabled |
| `pre970318` (**candidate**) | `3455808ab714d6d7a66aa4a3395150a24f29997bf50a9323653612af0f87b187` | the above, plus `function.c` returned to its state before `38b610ed8e01` (`bin/revert-970318.py`, four lines) |

These are reversions of two dated upstream commits, not behavioral patches invented from the originals; they reconstruct the trunk's state before 1997-03-18 in the two files whose later state is measurable in the corpus.

The second artifact is the pure trunk snapshot itself: `build/compiler-fit/bin/Dockerfile.trunk` downloads `gcc-mirror/gcc` at `2b3600acb4ec`, adds the files the git history lacks (`configure`, `version.c`, `obstack.[ch]`, `c-gperf.h`, `getopt.c`, `gstab.h`, `stab.def`, `hash.[ch]`, `tlink.c`, `move-if-change`, the i386 Linux `xm-linux.h` headers) from the CDK tree, applies the same obstack and little-endian patches, generates the parsers with byacc as the CDK Makefile does (`bin/byacc-wrap` reorders the `-o` option for byacc 1.9), and builds `cc1` (SHA-256 `c4b82c51976e87e365a26c37b8281596e389ec3209ec5a59cd22ec2cf01cc686`, banner `trunk-19970318`). None of the borrowed files takes part in code generation. That snapshot's C front end emits an exception-unwinder library call in every function unless `-fno-exceptions` is passed, which is why the row without it scores zero; with it, the results equal the CDK-based candidate on every measurement in this note.

Reproduce the corpus run (from the project root):

```sh
LOADER=$(node -p "require.resolve('tsx', {paths:['../psx-decompilation-harness']})")
node --import "$LOADER" build/compiler-fit/compare.mts \
  --compiler=build/compiler-fit/bin/cc1-cdk970404-pre970318 \
  --name=cdk-970404-pre970318-mipsas --drop-flag=-mgas --alt-flag=-mmips-as
```

The runner is the previous session's `build/sn281-trial/compare.mts` generalized with `--compiler`, `--name`, `--drop-flag`, `--alt-flag`, `--member` and `--variant=<member>:<symbol>:<file>`; it keeps the baseline compile, the identical preprocessed bytes, the production assembler and the whole-member oracle, and refuses to run if tracked state changes. Reports: `build/compiler-fit/<name>/report.json` and per-member directories.

## 5. Migration path for the C members

**Status 2026-10-17 (later the same day): installed.** Production now selects the pure trunk snapshot: `toolchain.json` names `tools/vendor/gcc/trunk-19970318-psx` as the compiler source, `build/dependencies/compiler/gcc-trunk-19970318-psx/cc1` as the binary, version `trunk-19970318`, and `-mmips-as -fno-exceptions` in place of `-mgas`. The recipe is tracked at `tools/gcc-recipes/trunk-19970318-psx/` (`provision.sh` rebuilds and installs it; `install.py` refuses any `cc1` whose hash differs from `expected-cc1.sha256`). `npm run compiler-source -- verify` reports the tree and binary binding verified; the `gcc-rtl` analysis profile was re-bootstrapped. Both `CC1FLAGS_` overrides and their autoloop allowlist entries were removed; `87-realloc3` now compiles all three functions from C (`func_000001A0.c` is the common-return copy helper, `func_0000014C.c` the plainer spelling); `libc/48-memmove` and `libc2/9-memmove` were installed from the probe source. The full re-verification result is recorded at the end of this section. The list below is the plan as it was measured before the switch.

1. **No source changes are required for the 137 existing members.** Under the candidate they match as they are (`build/compiler-fit/cdk-970404-pre970318-mipsas/report.json`).
2. **The byte-copy helper becomes C.** `build/sn281-trial/copy-common-return.c` (and the earlier `build/memmove3-reopened/guarded-labels.c`) make `87-realloc3.o` a 108/108 match with `realloc3`, the rollback helper and the copy helper all compiled from C (`…/copy-ov/copy-copy-common-return-report.json`). This is the witness the previous session could not obtain under 2.7.2 (4 words short) or Homebrew (1 word short).
3. **Both allocator flag overrides can be retired.** `86-free3.o` matches with `-fno-rerun-cse-after-loop` dropped (`…/free3-noov/`). For `87-realloc3.o`, dropping `-fforce-addr -fno-rerun-cse-after-loop` leaves one register-choice residual in the rollback helper with the current spelling; the plainer spelling `build/compiler-fit/respell/unfree3/v2-bp-locals.c` (`bp = _r_p.bp; bp->size = _r_p.size; …`) matches with no overrides at all (`…/unfree3-noov/`). The override comments in `configs/flag_overrides.mk` were describing compiler behavior that the candidate has natively.
4. **Members that resisted 2.7.2 become reachable.** `libc/48-memmove.o` (identical text in `libc2/9-memmove.o`) matches from `build/compiler-fit/respell/memmove/guarded-return-walk.c` under the candidate and under stock CDK, and fails under 2.7.2 and Homebrew 2.8.1. The 141 members with the jump-fill fingerprint are the natural next targets.
5. **Toolchain changes needed** (for the user to approve): `toolchain.json` `tools.cc1` → one of the two binaries (runtime dependency) and `compiler.version`/`compiler.source` → a project-owned recipe (`tools/vendor/gcc/trunk-19970318/` with `Dockerfile.trunk` and `byacc-wrap`, or `tools/vendor/gcc/cdk-970404-pre970318/` with `Dockerfile.cdk` and `revert-970318.py`, each with a `pin.json` as for the 2.7.2 recipe); `flags.cc1`: replace `-mgas` with `-mmips-as` (or backport the split switch and add `-mno-split-addresses`), and add `-fno-exceptions` for the trunk build; delete both `CC1FLAGS_` overrides after installing `v2-bp-locals.c`; install the copy helper C; re-run `check-all` to regenerate all verification receipts; re-bootstrap the `gcc-rtl` analysis profile against the new binary (`npm run analysis-support -- bootstrap`). The 625 assembly TUs and the `sn-aspsx` profile members are unaffected.

## 6. What this does not settle

- The lower bound was originally taken from DCB's objects. Since 2026-10-18 both bounds are confirmed locally (section 8), each to a single commit, on the project's C members and on Sony's own HMD C. Still unconstrained: about 1,260 backlog members whose symbol tables show GCC origin have no C yet, and could show a February–March 1997 behavior the pin lacks.
- DCB also needed a *second* profile (a later 2.8-era snapshot, still text-epilogue, no post-reload CSE) for part of libsnd/libcd/libgs/libc2. None of those members are in our corpus, so a per-member compiler profile may eventually be needed.
- **The optimisation level.** libhmd was built with `-O3`: Sony's makefile says so, and the replay at `-O3` strictly dominates `-O2`. All 161 reconstructed members still match in code at `-O3`, so no measured member needs `-O2`. A single global `-O3` therefore fits all the evidence. Per-library levels would be needed only if some library is later shown to require `-O2`; a member that matches under one level only is evidence for its library.
- **24 of Sony's HMD C objects still differ in ordinary code** (section 8). No compiler snapshot inside or at the edges of the window, no other available compiler, and no single flag reproduces them. The most likely cause is that the disclosed Release 4.4 sources are not exactly what built the 4.7 members. They are not evidence against the pin.
- The Cygnus-local code in the CDK tree (regmove on by default, `losing_caller_save`, mips.md and expr.c local hunks) showed no effect on 137 members, and the pure trunk build reproduces the same results, so it is not part of the identification.
- Whether Sony's build was literally a Cygnus progressive release or an FSF snapshot is not decidable from bytes; the two differ only in Cygnus-local hunks that this corpus does not exercise.

## 7. Artifacts

- Censuses and their JSON: `build/compiler-fit/epilogue-census.py`, `return-slot-census.py`, `split-store-census.py`, `jump-fill-census.py`, `lib-timestamps.py` (PSYLIB member timestamps are archive times, 2000-02-16, except LIBGUN/LIBTAP 1997-09-22; they do not date compiles).
- Compiler builds: `build/compiler-fit/bin/` (binaries, `Dockerfile.cdk`, `revert-970318.py`, `Dockerfile.trunk`, `byacc-wrap`).
- Pure-trunk corpus report: `build/compiler-fit/trunk-19970318-mipsas-noeh/report.json` (and `trunk-19970318-mipsas/` for the run without `-fno-exceptions`).
- Corpus reports: `build/compiler-fit/{cdk-970404,cdk-970404-mipsas,cdk-970404-noreloadcse-mipsas,cdk-970404-pre970318-mipsas,*-noregmove}/report.json` and logs; probes under each run's `copy-ov/`, `copy-noov/`, `unfree3-noov/`, `free3-noov/`, `memmove/` subdirectories.
- Dumps proving the allocation mechanism: `build/compiler-fit/dumps/{realloc2,first}-{272,cdk}/in.i.{flow,lreg,greg,sched}`.
- Respelling probes: `build/compiler-fit/respell/`.
- External sources consulted: `ser-pounce/cdk-gcc` b18, `decompals/old-gcc` (CDK recipe and patches), `ReGame-Labs/dcb_decomp` (`tools/patch_cc1.py`, `tools/sn_cc1.py`, `config/us/psyq_objects.txt`), `Fuuzetsu/tenchu-decomp` (`docs/toolchain.md`), `gcc-mirror/gcc` commits `38b610ed8e01`, `2a9fb5489fc5`, `8acd7d300281`, `5ef37cd33952`, `cabcf079ea40`.

## 8. Confirmation on Sony's own source, and the window's edges (2026-10-18)

Sections 1–6 were measured on the project's reconstructions. That C was written
under the compiler being tested ([methodology](compiler-identification-methodology.md)
§1), so it cannot be fully independent evidence. Sony's own source can.

- **The source.** The SDK ships 163 Sony-authored libhmd `.C` files, 192 `.ASM`
  files and the makefiles that build the archive members (local only:
  `library-input/psyq/SRC/LIB/HMD`). Its readme says they are "completely the
  same as those used in SCEI to create libhmd".
- **The comparison.** Every object is compared with its shipped member by
  **whole-file SHA-256**. That is stricter than the whole-member oracle of
  sections 1–5: it also covers symbol numbering, record order and fixup order.

**Method: replay the producer's build.**

- Each object listed in `MAKE1/2/3.MAK` is built from its own source with its
  own `-D` defines (`-DXYZ`, `-DBACK_FACE`, …), at the makefile's `-O3`.
  DMPSX runs only where the makefile runs it.
- The rest of the chain: CRLF→LF lower-case views of the immutable SDK headers;
  the pinned `cccp`; the candidate `cc1` with the production flags; the period
  `as`; the declared DMPSX stage; and an experimental ECOFF→LNK encoder that
  reads only the candidate (harness `plans/toolchain-provenance/completion-plan.md`
  §2.2).
- 575 listed objects (305 C, 270 ASM) correspond to members of `LIBHMD.LIB`.

**Results with the pinned `cc1` (`c4b82c51…`):**

| Set | Whole-file identical |
| --- | ---: |
| C objects at `-O3` | **275/305** |
| C objects at `-O2` (current production flag) | 273/305. `-O3` adds `03000000` and `MIME` and loses nothing |
| C objects at `-O3`, with the DMPSX C-macro table the SDK documents | **281/305** |
| ASM objects | 270/270 |

- **libhmd's optimisation level is `-O3`.** Sony's makefile says so, and the
  replay confirms it. The 161 staged project C members are indifferent: 161/161
  match in code at both `-O2` and `-O3`
  (`compiler-window-bisect/eval/pin-O3-projectC.json`).
- **The documented DMPSX table.** Thirteen C objects use C-only DMPSX
  placeholders (`gte_rtv0_b` = `0x13f`, …). The harness stage rejects them,
  fail-closed. The table that resolves them is fully determined by two SDK
  documents: the 65 placeholder words of `INLINE_C.H` and the 65-row "DMPSX
  Inline Function Table" of the Inline Programming Reference (Release 4.4). All
  rows join, and the 17 IDs shared with the assembly-side table agree.
- **The 24 C objects that still differ** all differ in ordinary code; GTE words
  and packaging agree. Twelve are the quad active-subdivision objects
  (`0008001x`, `000a001x`, `000c005x`). Their sources include the four `DA*4_CM.C`
  fragments, and all twelve triangle siblings match. The quad driver tests
  `ifo->flg & 0x80000000` (and the same mask on `flg0`) where the triangle
  fragments write `flg < 0`. Sony's objects keep `and` against `0x80000000`
  hoisted into a register before the loop, with one more spill (frame 80
  against 72). The pin turns the first test into `bgez`. Of the other twelve:
  - six are environment-map objects (`0600xxxx`, a "Beta" feature in the 4.7
    release notes);
  - two use the same mask four times (`05000000`, `05000001`), probably the same
    mechanism (unchecked);
  - four have no such test (`00050048`, `04010010`, `04010011`, `04010020`).

**Window bisect.**

- *Recipe.* The production recipe was parameterised by gcc-mirror commit. Given
  the pin's commit and version string, it reproduces the pinned `cc1` byte for
  byte, from the pinned tarball.
- *Scoring.* Each snapshot is scored on two independent suites, holding the
  preprocessor, assembler and flags fixed: the 161 staged C-form project members
  (from their preprocessed inputs) and the Sony HMD replay.

| Snapshot | Project C, code match | Sony HMD C, whole-file |
| --- | ---: | ---: |
| 1997-01-22 (`69ce75dc0deb`) | 148/161 | 229/305 |
| `4757e6a402f5` (1997-02-05 00:29, the commit before the lower edge) | 160/161 (`libc2/33-prnt` breaks) | 247/305 |
| **`cabcf079ea40`** (1997-02-05 16:20, reload stack slots no longer aligned to BIGGEST_ALIGNMENT) | **161/161** | **275/305** |
| 1997-02-05 20:57, 02-15, 02-24, 03-05, 03-12 | 161/161 | 275/305 |
| pin `2b3600acb4ec` (1997-03-18 18:38) | 161/161 | 275/305 |
| `38b610ed8e01` (1997-03-18 20:00, register-parameter REG_EQUIV) | 157/161 (`realloc2`, both `qsort`s, `bsearch`) | 245/305 |

- **Both edges are confirmed on local evidence.** The lower edge is now a single
  commit, confirmed on local evidence (section 3 had it from DCB). The upper edge
  is confirmed on four project members and 30 of Sony's objects.
- **The interior is flat at every sampled point.** Not every commit was built.
  On every member measured, the choice of snapshot inside the window makes no
  difference. The pin is kept for coherence with the assembler pin.
- **No snapshot reproduces any of the 24.** Neither do CDK 970404 (stock,
  noreloadcse, pre970318), GCC 2.7.2-psx, GCC 2.95.2-psx, any of 20 single-flag
  toggles, or unsigned `flg`/`flg0` declarations in the quad structures.

**Evidence (local, git-ignored):**

- `build/toolchain-provenance/compiler-window-bisect/`: recipe variant,
  `build.sh`, `evalCompiler.ts`, the commit list, per-snapshot results and the
  built compilers;
- `build/toolchain-provenance/lnk-encoding-research/`: `hmdReplay.ts`,
  `hmdProbe.ts`, `dmpsxCTable.ts`, `results/`.
