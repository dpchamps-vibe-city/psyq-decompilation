# REALLOC3 and compiler provenance: consolidated session report

This is the single entry point for the session's reconstruction, compiler-provenance research, SDK inspection, Homebrew Psy-Q 2.8.1 trial, and copy-helper investigation. It distinguishes local measurements from published reports and from questions we have not settled. Detailed evidence remains in the linked notes and artifacts.

## 1. Bottom line

- **`realloc3` was recovered and committed:** 57/57 function words, with exact-diff, full-build, scope and clean-source finalization passing. Commit: `0759b22` (`match libapi_87::realloc3`).
- **The private byte-copy helper is still unresolved.** Under unmodified Homebrew Psy-Q 2.8.1, the best clean-C candidate matches 107/108 whole-member words, but one instruction and its associated relocation differ. This is **not a match**.
- **Production remains the configured GNU-based GCC 2.7.2 rebuild.** It is not an authenticated original Sony/SN compiler executable. Earlier notes calling it “Sony GCC 2.7.2” overstated its provenance; that wording is superseded here.
- **Homebrew 2.8.1 is a concrete, measured reconstruction; equivalence to this object's historical producer remains unproven.** Its controlled trial did not justify a global migration.
- **The original producer of this exact allocator member remains unidentified.** Neither an SDK release label, a GCC version string, a compatible game compiler nor a near-match establishes that identity.
- No compiler patch, instruction-output repair, per-function compiler mixing, relocation masking or new policy exception was used to manufacture a completion.

### Detailed notes

| Topic | Note |
| --- | --- |
| Verified `realloc3` reconstruction and CSE mechanism | [realloc3-cse-loop-boundary.md](realloc3-cse-loop-boundary.md) |
| Earlier copy-helper investigation and harness limitations | [realloc3-copy-compiler-variant.md](realloc3-copy-compiler-variant.md) — historical record; its baseline “Sony” attribution is superseded above, and its earlier alternatives are not active recommendations |
| Public compiler research and pinned references | [sn-compiler-community-findings.md](sn-compiler-community-findings.md) |
| Controlled Homebrew compiler/corpus comparison | [homebrew-psyq-281-trial.md](homebrew-psyq-281-trial.md) |
| Best copy candidate, exact residual and native compiler trace | [sn281-copy-return-boundary.md](sn281-copy-return-boundary.md) |
| **Later (2026-10-17): compiler identified as a Feb–Mar 1997 GCC trunk snapshot; copy helper matched in C; migration path** | [compiler-identification-1997-trunk.md](compiler-identification-1997-trunk.md) — supersedes the provenance conclusions below |

Paths beginning with `build/` are local experimental evidence, normally ignored by Git. They are not guaranteed to survive cleaning. Paths in the following sections are project-relative unless stated otherwise.

## 2. Original target and acceptance boundary

The original member is `library-input/redux/libapi/87-realloc3.o`:

```text
SHA-256 432bbcee5061fc2ba2287384b69383bcd9e5893ef0998574d032a969063fba22
member  libapi_87
```

It contains:

| Function | Role | State |
| --- | --- | --- |
| `realloc3` | Resize allocator payload, including allocation/free/rollback/copy paths | Recovered and committed this session |
| `func_0000014C` | Restore free-list snapshots after failed growth | Already reconstructed C |
| `func_000001A0` | Overlap-safe directional byte copy | Live source remains `INCLUDE_ASM` |

The original `.text` has 108 words: 57 for `realloc3`, 21 for rollback, and a 30-word copy range including padding. The copy starts at **ELF section offset `0x138`**. The historical private symbol name `func_000001A0` and other printed disassembly coordinates are not that section offset.

One original member is one translation unit. A credible completion must preserve the whole member's program sections, bytes, symbols/storage and symbolic relocations. Matching one function while breaking a neighbor is not an integrated result. Mixing compiler outputs inside the member or discarding padding/relocations is not an acceptable substitute.

The verified member receipt following the `realloc3` repair was 108/108 **with the copy helper still assembly-backed**. It did not establish three C reconstructions. The later Homebrew proof attempt explicitly compiles all three from C, but fails the oracle.

## 3. What recovered `realloc3`

The semantic reconstruction was not the main remaining difficulty. The ordinary pointer expression let the compiler fold a header load into `ptr - 4`; the target retained `bp = ptr - 8` and then loaded at `bp + 4`.

The successful source separates the calculations:

```c
rounded_units = (size + 7) >> 3;
do {
    bp = (Block *)((u8 *)ptr - 8);
} while (0);
old_units = bp->size;
new_units = rounded_units + 1;
```

The one-trip loop contributes a zero-width loop-end note, not a runtime branch. GCC's first CSE pass respects that region boundary. The native dumps and `cse.c` inspection explain why this placement preserves the header-pointer formation.

Two further distinctions mattered:

1. Moving the final `+ 1` after the header-field load resolved a scheduling residual.
2. Using separate `rounded_units` and `new_units` variables resolved the remaining allocation residual.

This worked with the **existing** owning-TU flags:

```make
CC1FLAGS_libapi_87 := -fforce-addr -fno-rerun-cse-after-loop
```

No new override or source-policy exception was introduced. Removing just the loop boundary later broke the member under both the baseline and Homebrew 2.8.1 no-split trial. It must not be removed as apparently redundant without remeasurement.

The source is a verified reconstruction, not proof of the historical author's exact spelling. Its operational behavior includes null-pointer allocation, zero-size freeing, equal-size return, shrinking by splitting/freeing a tail, and growth with rollback on allocation failure.

### Why the previous park did not settle it

At reopening, the ledger contained 50 measurements but only 23 distinct compiled outputs. Prior closures concerned particular source families and an older flag context. They were not impossibility proofs over all C.

The decisive new axis was a CSE-region boundary, not another cast spelling. This is a concrete example of why a closure must retain its source, compiler and context premises.

Evidence and intermediate staged residuals: [the verified reconstruction note](realloc3-cse-loop-boundary.md), `build/realloc3-reopened/`, and `build/pipelineReversal/libapi_87::realloc3/`.

## 4. Compiler provenance: what the names actually establish

### Current project compiler

`toolchain.json` selects GCC 2.7.2 at:

```text
build/dependencies/compiler/gcc-2.7.2-psx/cc1
SHA-256 0359379289db8e3904b8ed3b25b422ca631c8d71ab2f543d533c39ed2967764f
```

The inspected recipe starts with upstream GNU GCC 2.7.2, applies PSX target/ABI, little-endian/section and host-build compatibility changes, and builds a native executable. We found no project-authored optimizer or scheduler modifications in that inspected recipe. This does **not** turn it into an authenticated SN distribution.

The `[AL 1.1, MM 40] Sony Playstation` target banner is not distribution provenance. The source/binary binding is recorded in `tools/vendor/gcc/2.7.2-psx/pin.json`; the public old-gcc tooling revision inspected was `c8c4b40f105375d575c030b28f23d6370d676268`.

### Why this project selected 2.7.2

- Initial commit `1dae33d` selected GCC 2.95.2.
- Commit `ee3df32` (`Configure GCC 2.7.2 and match SpuGetTransferStartAddr`) changed the global compiler to 2.7.2 and changed `-G8` to `-G0`.
- The commit title identifies a demonstrated match, not an exhaustive record of every consideration behind adoption.
- The Homebrew trial subsequently reproduced `SpuGetTransferStartAddr` under 2.8.1 **when split addresses were disabled**. That example therefore does not uniquely discriminate GCC 2.7.2 from 2.8.1.

Compiler version, target defaults, explicit flags and assembler behavior must be separated experimentally. Changing several together cannot isolate a version effect.

## 5. What the supplied SDK tree showed

Scan root:

```text
/home/dave/Documents/code/btn-decompilation/tools/vendor/psyq_sdk/psyq
```

The read-only investigation covered 124 PDFs, release notes, archives and executable strings. The tree contains mixed generations; its directory label is not a compiler identity.

### Executables inspected

| Relative to scan root | Observed identity | SHA-256 |
| --- | --- | --- |
| `psyq/CC1PSX.EXE` | `2.7.2.SN.1` | `d383902b6ed1a32668333f7a57c6bacb22466e41c88761ddbe8add24858fb418` |
| `bin/CC1PSX.EXE` | `2.95.2 19991024 BUILD 4.0.0030` | `0755e509f148b6018e97e89e798493af37c290a44fc97ecd1ec661182ed56e65` |
| `bin/CPPPSX.EXE` | `2.95.1 SN32 BUILD 4.0.0022` | Identity inspected separately from CC1 |

Static banner-reference inspection classified the older executable's `2.6.3` string as its **host compiler version**, not its own compiler version. Merely finding multiple GCC strings would have produced the wrong attribution.

These binaries were not established as execution-based compatibility oracles for our allocator member in this work.

### Release/source-archive evidence

| Document | What it says |
| --- | --- |
| `psx/CHANGE.TXT`, release 4.3, May 1998 | GNU 2.8.0 compiler tools |
| `psx/LIBCHG_E.TXT`, release 4.4, October 1998 | GNU 2.8.1 tools and `gcc281s.zip` source archive |
| `zips/Lib45.zip:Libchg_e.txt`, release 4.5, February 1999 | Updates `gcc281s.zip` and adds `gcc272s.zip` |
| This project's `library-input/psyq/LIB/readme.txt`, release 4.7, February 2000 | Adds `gcc295s.zip` and deletes `gcc281s.zip` |

The named compiler source archives were **not found in the scanned tree**. That is a local absence finding, not a claim that they no longer exist elsewhere.

The documents identify distributed tools. They do not establish which compiler produced every prebuilt library object, or whether an unchanged member was retained rather than rebuilt.

## 6. Public research: leads, not locally reproduced authority

The pinned links and fuller quotations are in [sn-compiler-community-findings.md](sn-compiler-community-findings.md). The principal findings were:

- **Homebrew Psy-Q:** a public GCC 2.8.1 reconstruction exists. The inspected import changes `mips.h` and adds `psx.h` and `xm-psx.h` to an upstream-GCC tree. It is not evidence for an entirely separate optimizer fork. The author reports reproducing an MGS build, with a checked-in test pinning SDK and game revisions. We did not reproduce that external test or independently authenticate the imported files against the original SDK source archive.
- **psyq-wasm:** derives from the same reconstruction. Comparing a native and WebAssembly build of the same sources is useful, but not independent calibration against an original SN executable.
- **Tenchu:** published complete-member comparisons distinguish 2.7.2-compatible objects, compiler-invariant objects, and a member matching both 2.8.0 and 2.8.1. `GS_119` is reported unchanged across releases 4.3–4.6. Its `GS_107` backend is explicitly reconstructed from observed behavior, not claimed to be authenticated historical Sony source. Return/block-copy differences are relevant leads, not our diagnosis by analogy.
- **Digimon Digital Card Battle:** published tooling patches compiler binaries, including return eligibility and epilogue/liveness behavior. This documents observed incompatibilities, but patched success is not identification of a released historical compiler and is not authorization to apply those patches here.
- **Tombi:** the leading update changes the reference from an older DOS compiler to a Win32 build because scheduling differs. Older contradictory text remains below it. A reported native checker covers 628/636 reference-verified functions, not universal equivalence.
- **Armored Core:** compares eleven game functions across nine compilers. That is game-code evidence, not proof about the producer of precompiled SDK members.
- **SDK-dump documentation:** independently warns about mixed older documentation and newer compiler executables, consistent with our local scan.

Unavailable or mismatched search-result URLs were not treated as checked evidence. None of this literature identifies the producer of our exact `87-realloc3.o`.

## 7. Comparison with BTN

The sibling project `../btn-decompilation` currently selects **GNU-based GCC 2.95.2**, not Homebrew 2.8.1:

```text
tools/vendor/old-gcc/build-gcc-2.95.2-psx/cc1
SHA-256 2aa85925dfa10855107c78e29ec36965b953976a45b1a47fb68beb5a74096079
```

Its Makefile selects the executable, and its recipe starts with upstream GNU 2.95.2 plus PSX/MIPS and host-build patches. It also vendors Homebrew Psy-Q as reference material and had previously tested it; presence in the tree is not active selection.

BTN's historical notes describe native-versus-original-SN comparisons, including game functions. Those notes were read, not rerun here. BTN's game compiler selection does not identify the compiler that produced separately linked SDK library objects.

## 8. Controlled Homebrew 2.8.1 trial

The user authorized a diagnostic trial, not an unconditional migration.

### Exact alternative identity

```text
../btn-decompilation/tools/vendor/homebrew-psyq/build/psyq-4.4_old-school/gcc-2.8.1/cc1
SHA-256 61fd8afeeeb3f86028eabf222aa6ceda5072924f1caa4553d5570a700616cbfd
```

Banner:

```text
GNU C version 2.8.1, Psy-Q 4.4, Homebrew Psy-Q 0.2.0 (mips-psx)
compiled by GNU C version 2.7.2.3.
```

The clean local checkout is `8b01a6e8746e3fe7ce1cc45f5992ef71b5d62c1f`. Its public parent is `bdee891005a0aec6bf6fe40e504cf068ebf38caf`; the additional local commit adds two static-build scripts, not backend changes. The existing executable and checkout were inventoried separately. This was not a fresh reproducible compiler build.

### Experimental controls

Runner: `build/sn281-trial/compare.mts`.

- Freshly compile the baseline from the real, ordered original TU.
- Give Homebrew the **identical preprocessed bytes and logical filename**, including neighboring functions and declarations.
- Preserve the original member's assembler/profile and established `move`-to-`addu` handling; do not replace all assemblers globally.
- Compare through the normal whole-member relocated-object oracle.
- Retain raw assembly, commands, hashes, diagnostics and both objects.
- Test both unchanged explicit flags and an alternative with `-mno-split-addresses` appended.

Homebrew repeatedly emits conflicting `.file 1` filenames for included C fragments, which modern GAS rejects. A diagnostic adapter suppresses **only those conflicting debug metadata rows**, outside `#APP`, retaining raw output. It patches no instruction, label, storage or relocation directive. This is not installed production support.

### Corpus results

Selection: 137 C-bearing members across 15 libraries; 121 fully C and 16 mixed C/assembly backlog.

| Compiler/settings | Exact whole members / 137 | Exact fully-C members / 121 |
| --- | ---: | ---: |
| Current 2.7.2 baseline, fresh builds | 137 | 121 |
| Homebrew 2.8.1, same explicit flags | 115 | 110 |
| Homebrew 2.8.1 plus `-mno-split-addresses` | 124 | 113 |

All selected members compiled and assembled after debug metadata handling; no rejecting C diagnostics were detected.

Important limits:

- Existing C was developed against the baseline; failure of unchanged C is not historical exclusion of 2.8.1.
- 109 of 121 fully-C members contain at most eight words. Among the remaining twelve, Homebrew defaults match three and no-split matches five. The headline totals are not broad equivalence evidence.
- Mixed-member successes do not mean their assembly-backed functions were reconstructed.

The thirteen no-split incompatibilities were:

- Fully C: `libapi/14-c160`, `77-padstop`, `79-malloc2`, `81-realloc2`, `82-calloc2`, `85-malloc3`; `libmcx/2-mcxcmd3`; `libsnd/216-vs_vtc`.
- Mixed: `libapi/72-counter`, `73-sc2b`, `75-first`, `76-pad`; `libsnd/51-ssclose`.

The significant correction is that **`SpuGetTransferStartAddr` matches under Homebrew no-split**. The earlier disagreement was confounded by split-address defaults; that function is not a unique compiler-version fingerprint.

Reports: `build/sn281-trial/report.json` and `build/sn281-trial/no-split-addresses/report.json`. No production switch followed.

## 9. The copy-helper proof attempt

### Recovered operation

The candidate copies bytes backward when destination is at or above source, forward otherwise, performs no accesses for zero count, and returns the original destination. The caller ignores the return value. Its pointer return interpretation is consistent with the observed operation, not independently established by a public prototype for this private helper.

Natural `while (count--)` source let the loop optimizer introduce descending pointer walks. Guarded label loops retain the target's indexed backward accesses and incoming-count post-decrement behavior. The best candidate keeps those loops but uses **one common return after the `if/else`**:

```text
build/sn281-trial/copy-common-return.c
SHA-256 e855491cb807d75039e74d1613ac16c855ce0a74fa7f2d391833b8a4e95c019d
```

It is ordinary C, with no inline assembly, register pinning, volatile workaround or intrinsic. Both neighboring functions remain unchanged C in the same TU.

### Progression and exact defect

| Candidate/context | Whole-member result |
| --- | --- |
| Guarded copy draft, production 2.7.2 | Mismatch, 104/108 words |
| Same draft, Homebrew no-split | Mismatch, 105/108 words |
| Common-return draft, Homebrew no-split | **Mismatch, 107/108 words** |

These are localization counts, not a source-distance metric or terminal acceptance.

The best candidate has exactly one differing `.text` word:

| Section offset | Original | Candidate |
| --- | --- | --- |
| `0x170` | `0x08000069`: `j .text+0x1a4` | `0x03e00008`: `jr ra` |

The original local `R_MIPS_26` relocation is consequently missing. The delay-slot `move v0,t0`, both loops, final shared return, padding and both neighboring C functions agree. Neither the instruction nor the relocation may be masked away.

Fresh proof-attempt receipt: `build/sn281-trial/copy-proof-attempt.json`, explicitly marked **`NO_MATCHING_C_WITNESS`**. Complete comparison: `build/sn281-trial/no-split-addresses/copy-copy-common-return/report.json`.

### What the actual compiler did

This diagnosis uses the **actual Homebrew executable**, not diagnostics silently run through the project's still-configured 2.7.2 compiler.

Its native `jump2` dump retains UID 61 as a normal jump to the final destination-setup block. Its `dbr` dump replaces it with a return. Read-only GDB observes:

1. `fill_slots_from_thread` fills the slot and redirects UID 61.
2. `make_return_insns`, `reorg.c:4330`, calls `reorg_redirect_jump(jump, NULL)` to convert it to a return.

Observed state: `reload_completed=1`, `profile_flag=0`, `regs_ever_live[31]=0`, frame total zero. The inspected `mips_can_use_return_insn()` permits the simple return in that state.

Traced and untraced assembly are byte-identical. No debugger state modification, skipped pass, compiler patch or instruction repair was used.

Artifacts: `copy-return-trace.gdb`, `copy-return-trace.log`, `copy-return-trace-identity.json` under `build/sn281-trial/`, plus native selected dumps under the candidate's `sn281/trace/` directory.

### Alternatives measured, not solutions

- Named common-return labels and a one-trip wrapper around the return reproduce the same 107/108 residual.
- Separate branch-local result assignments reproduce the earlier three-word tail residual.
- Exhausted-counter conditional exits leave extra branch differences; they are not late-folded unconditional-jump witnesses.
- `-fno-thread-jumps` leaves the same 107/108 defect.
- `-fno-crossjumping` is rejected by this compiler; it is not an available flag workaround.
- `-fno-delayed-branch` changes scheduling across the member and grows it to 112 words; it does not solve the helper or owning TU.
- Returning `d + (count + 1)` in the backward arm retains arithmetic and changes register use: 90/108, not a match.

The ledger closures are **source/compiler/context-scoped**. They do not prove that every clean C construction, every flag set or every historical SN build is impossible. A genuinely different RTL/return-label construction or independently justified compiler context would be new evidence; another spelling producing the same output would not.

### Semantic test, separate from instruction identity

A C89 host test includes the exact common-return body with only its `u8`/`s32` typedef header substituted. It passes **66,560** comparisons against `memmove`: offsets 0–31 for source/destination, lengths 0–64 in a 128-byte buffer, including both overlap directions, disjoint/equal ranges, zero count and returned destination.

This is not PSX byte identity and does not establish behavior for invalid or negative lengths. Artifacts: `build/sn281-trial/test-copy-semantics.c` and `copy-semantics.log`.

## 10. Harness lessons established by the work

1. **Do not turn scoped closures into universal impossibility claims.** Preserve source, flags, toolchain identity and context; deduplicate identical compiled outputs before treating spellings as new experiments.
2. **Address-offset inventories need base provenance.** `ptr-4` and `(ptr-8)+4` can denote the same access. A multiset difference alone is not proof of a semantic defect.
3. **Zero-width compiler notes are part of the mechanism.** They can affect CSE regions, allocation and delay scheduling despite leaving no runtime instruction. Executable-CFG-only searches miss this axis.
4. **Check independent declarations.** Stale argument-register values do not imply extra callee parameters. A reported callee named `.text` was section-relative call representation, not a C declaration to invent.
5. **Separate tooling failures from reconstruction blockers.** Preparation omitted `size_t` while keeping `malloc3(size_t)`; the real TU compiled. A qualified-name jump-trace failure extracted zero sections despite native dumps being available through another route.
6. **Function extents and section padding differ.** A diagnostic can count 29 candidate words against a 30-word target range while the padding exists in the object section. The complete-member oracle remains authoritative.
7. **Compiler identity must travel with diagnostics.** Configured 2.7.2 tools do not automatically observe a manually invoked 2.8.1 candidate. Native dumps/debugger evidence were required for the latter.
8. **Version banners are not provenance, and corpus compatibility is not identification.** Keep upstream rebuilds, source reconstructions, SDK-tree executables and patched research backends distinct.
9. **One owning TU is the integration boundary.** The current harness's strict profiles vary flags/includes/assembler, not the compiler executable/source identity. A dispatch wrapper or stitched function output would not establish an accepted reconstruction.
10. **Match scope must be stated.** A full member containing original assembly is not all-C completion; semantic tests are not instruction matching; a one-word residual with a missing relocation is still failure.

These are measured limitations or interpretation lessons, not a claim that all corresponding harness fixes were implemented in this session.

## 11. Current decisions and remaining questions

### What changed

- `realloc3` C and its verified research note were committed in `0759b22`.
- Compiler research, corpus trials and copy candidates were preserved as notes and ignored build artifacts.
- This consolidated report adds documentation only; it does not authorize a commit or alter build inputs.

### What did not change

- Production compiler remains the configured 2.7.2 rebuild, with existing owner flags.
- The live copy helper remains its original `INCLUDE_ASM` placeholder.
- No Homebrew migration, new copy-helper completion, compiler/output patch or policy waiver was approved.
- Unrelated dirty files, including `calloc3.c`, were preserved. The experimental findings do not justify parking the production helper as globally impossible.

### Still unresolved

1. A **clean-C, whole-member exact witness under the measured Homebrew 2.8.1 compiler**. The user's requested proof has not been obtained.
2. Independent identification of the historical compiler/build/settings that produced this exact library member.
3. Whether other existing-C regressions under Homebrew reflect different required source shapes, target settings or genuinely different compiler behavior. The unchanged-source trial alone cannot decide.
4. Whether an independently calibrated original SN build would clarify the private helper's return-tail behavior. Published compatibility reports are not a replacement for such calibration.

### Reproduce the best measured attempt

From the project root, using the installed sibling harness:

```sh
LOADER=$(node -p "require.resolve('tsx', {paths:['../psx-decompilation-harness']})")
node --import "$LOADER" build/sn281-trial/compare.mts \
  --no-split --source=build/sn281-trial/copy-common-return.c
```

Inspect `build/sn281-trial/no-split-addresses/copy-copy-common-return/report.json`; the expected recorded verdict is **mismatch**, not match. The runner preserves production configuration and invokes the complete-member oracle. This command is an experiment, not integration or finalization.
