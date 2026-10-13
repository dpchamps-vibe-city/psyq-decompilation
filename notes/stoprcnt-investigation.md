# StopRCnt: resolved assembler-family mismatch and complete investigation record

**Current status (2026-10-13): integrated and finalized, whole-member MATCH
92/92.** Direct GAS with the named `move-addu` rewrite is now the configured
acceptance backend. The historical MASPSX residual was an assembler-family
mismatch, not a MASPSX defect or an allocation impossibility. See §19 for the
resolution. Sections 1–18 preserve the earlier investigation and its then-current
configuration; their unresolved-status statements are historical.

## 1. Historical status and principal findings

**StopRCnt remains unmatched. No candidate has been integrated, finalized, or declared impossible to reconstruct in clean C.** Its live source is still the original `INCLUDE_ASM` placeholder.

The recovered operation is straightforward:

```c
s32 StopRCnt(u32 counter) {
    D_000001E0[1] &= ~D_000001E8[counter & 0xFFFF];
    return 1;
}
```

Under the current production toolchain, this C produces a 13-instruction function. Ten instructions match the original. The remaining three calculate and use the mask-table address with `$at`, whereas the original uses `$v0`. The loaded mask and final return value still use `$v0` in both programs.

The latest authoritative comparison is a **whole-member MISMATCH**: 89 of 92 `.text` words agree, and the reported program-content difference is the three encoded instructions. The original member's data, symbolic relocations and linker-visible symbols are not reported as differing for this baseline. The 92-word extent includes member padding; it is not StopRCnt's instruction count.

The major findings are:

1. Numerous ordinary C spellings produce exactly the same compiled program. Making this operation look more elaborate has not solved it.
2. The candidate compiler emits the indexed mask load as `lw $2,D_000001E8($4)`. The production assembler pipeline introduces `$at` when expanding that form. It is not a C local allocated to `$at` by GCC.
3. The original compiler's assembly input is **unknown**. Original machine words do not establish whether it emitted that same pseudo-instruction or a separate explicit address sequence.
4. Selected compiler/version/flag comparisons did not produce a whole-member winner. These were not an exhaustive compiler-identification search.
5. Original-byte ASPSX fingerprints support a **conditional >=2.56 behavior class for COUNTER.OBJ**, not an exact assembler release. They do not establish 2.80 specifically.
6. A subsequent sweep of **201 ASPSX compatibility settings**, covering all six version-dependent states in the pinned MASPSX wrapper, produced **no match**. Every setting used `$at` for the mask address. All settings from 2.50 onward produced the same three-word baseline mismatch.
7. Several harness faults were found and repaired. Other diagnostic limitations remain, particularly incomplete value-web correspondence and misleading function-projection word counts.

**There is no demonstrated MASPSX defect.** The working direction is a possible compiler/backend/dialect/invocation mismatch, or another unestablished source/context difference. Neither direction has yet been proven to be the cause. The user explicitly required preserving MASPSX rather than pursuing assembler-defect claims.

This document records the current investigation, the separately audited fresh DeepSeek session, and the relevant earlier audit/cleanup history. It distinguishes measurements from interpretations and lists the limits of each experiment.

## 2. Target identity, ownership and scope

| Item | Identity |
|---|---|
| Function key | `lib_f5b70e00e12530c5_0::StopRCnt` |
| Selected input | `library-input/redux/libapi/72-counter.o` |
| Original PSY-Q member | `LIBAPI.LIB`, ordinal 72, `COUNTER.OBJ` |
| Live function fragment | `src/libraries/libapi/72-counter/StopRCnt.c` |
| Original TU manifest | `src/libraries/libapi/72-counter/tu.json` |
| Converted-original SHA-256 | `f9696b5b2525f5948c2e265374583b643e5fe7484870ce81a921db325f1c6c2b` |
| Native original LNK member SHA-256 | `72cff5d7ae33c313a9b3dbfe40b9837e2c79edab6b26e83bcd384c93e14ec1b7` |
| Native LIBAPI.LIB SHA-256 | `f4c2d61cbe1c55f01f7e0fdfe652a0771fc943f0e95e002ea1069a2774e7c41f` |
| Function coordinate | `.text+0x104`, 52 bytes / 13 words |
| Original member code extent | `.text`: 368 bytes / 92 words |
| Original member initialized data | `.data`: 32 bytes |
| Function-size annotation | Inferred from the original symbol boundaries, not an original nonzero ELF size annotation |

These are relocatable-object section coordinates, **not invented PlayStation RAM addresses**. The `D_000001E0`-style names are the disassembler's object-coordinate names, not the MMIO addresses stored in those objects.

The ordered production TU is:

1. `_shared-0.h`
2. `SetRCnt.c`
3. `GetRCnt.c`
4. `StartRCnt.c`
5. `StopRCnt.c`
6. `ResetRCnt.c`
7. `_data.c`

SetRCnt, GetRCnt and StartRCnt are existing exact C context. SetRCnt was solved and finalized by the separate fresh autoloop session during this investigation. ResetRCnt and member data remain reference backlog. StopRCnt experiments must not rewrite those neighbors to compensate for its residual.

### Authoritative acceptance contract

Every authored candidate is one function fragment substituted into that original ordered TU. The production compiler compiles the **whole TU**, and acceptance compares the **whole owning member**:

- allocated program-section bytes and extents;
- initialized versus zero-fill storage;
- linker-visible exports, imports and COMMON;
- relocation offsets, kinds, targets, encoded addends and supported HI16/LO16 grouping.

A function-only instruction listing is explanatory evidence, not a separate acceptance oracle. There is no isolated-function compilation followed by stitching, no original-object substitution for missing C, and no permissive partial-member match.

### Preservation requirements followed

- No StopRCnt live-source integration or neighboring-source edit.
- No changes to the compiler binary/source, MASPSX source/revision, production flags, or reference assets.
- Diagnostic flag/version alternatives were confined to build artifacts. The later compatibility sweep was explicitly requested by the user.
- No hard-register pinning, inline/top-level assembly, assembler-label tricks or flag tricks presented as a C solution.
- No commits, staging, worktrees, process interruptions, or unsolicited project-wide binary verification.
- The user's `.pi/autoloop.json` modification and existing harness repairs were preserved.
- The three note deletions previously requested as cleanup were not restored.

## 3. Actual data layout and operation

The relevant original data are:

| Object | `.data` offset | Contents / meaning |
|---|---:|---|
| `D_000001E0` | `0x00` | Pointer initialized to MMIO `0x1F801070` |
| `D_000001E4` | `0x04` | Pointer initialized to MMIO `0x1F801100` |
| `D_000001E8` | `0x08` | Six mask words: `{0x10, 0x20, 0x40, 1, 0, 0}` |

`D_000001E0[1]` consequently addresses the word at `0x1F801074`, the interrupt-mask register. StopRCnt clears the selected table mask from that word and returns 1. It does not access the root-counter mode/count/target records through `D_000001E4` in this function.

The current shared declarations are supplied by the original TU's scope:

```c
extern u32 *D_000001E0;
extern u32 D_000001E8[6];
extern volatile RootCounterRegisters *D_000001E4;
```

`RootCounterRegisters` has 16-bit count/mode/target fields at offsets 0/4/8 and a 16-byte record stride. Its declaration is neighboring context, not an extra StopRCnt operation.

**Correction to existing comments:** StartRCnt's comment and earlier grouping prose describe the fourth mask as `0x100`. The original data word is **1**, not `0x100`. The actual bytes, rather than those comments, were used throughout the investigation. Neighboring source/grouping comments were not opportunistically edited.

The target masks the argument with `0xFFFF` but performs no additional bounds check on the table index. Candidates did not invent a guard, alternate error return, or additional counter-register access.

## 4. Original instructions and exact baseline difference

The original 13-word sequence is:

```asm
.text+0x104  andi a0, a0, 0xffff
.text+0x108  sll  a0, a0, 2
.text+0x10c  lui  a1, HI(D_000001E0)
.text+0x110  lw   a1, LO(D_000001E0)(a1)
.text+0x114  lui  v0, HI(D_000001E8)
.text+0x118  addu v0, v0, a0
.text+0x11c  lw   v0, LO(D_000001E8)(v0)
.text+0x120  lw   v1, 4(a1)
.text+0x124  nor  v0, zero, v0
.text+0x128  and  v1, v1, v0
.text+0x12c  addiu v0, zero, 1
.text+0x130  jr   ra
.text+0x134  sw   v1, 4(a1)             # return delay slot
```

`HI`/`LO` here are readable notation for the symbolic relocation relationship. The actual converted object uses `.data` relocations, with an encoded addend of 8 for the mask table.

The baseline difference is exactly:

| `.text` offset | Original word / instruction | Candidate word / instruction |
|---:|---|---|
| `0x114` | `0x3c020000`: `lui v0,0` | `0x3c010000`: `lui at,0` |
| `0x118` | `0x00441021`: `addu v0,v0,a0` | `0x00240821`: `addu at,at,a0` |
| `0x11c` | `0x8c420008`: `lw v0,8(v0)` | `0x8c220008`: `lw v0,8(at)` |

Both programs load the mask into `$v0`. Only the temporary address register differs. The target is a straight-line leaf with no calls and no loop. Startup frame analysis reported a zero-sized target frame.

### Latest literal project-alias candidate

File: `build/stoprcnt-solve/project_aliases.c`.

```c
#include "common.h"

s32 StopRCnt(u32 counter) {
    D_000001E0[1] &= ~D_000001E8[counter & 0xFFFF];
    return 1;
}
```

A fresh production diff of this exact source produced the whole-member 89/92 MISMATCH above. Evidence:

`build/libraries/candidates/lib_f5b70e00e12530c5_0/f3346f53-d25f-4486-9757-ade0c9a092be/comparison.json`

The subsequent ASPSX-mode sweep also compiled a fresh production baseline through the normal whole-TU helper before varying assembler compatibility settings.

### SDK spelling tested separately

The SDK declaration is `long StopRCnt(unsigned long)`. The literal SDK-type candidate was:

```c
#include "common.h"

long StopRCnt(unsigned long counter) {
    unsigned long *interrupts = (unsigned long *)D_000001E0;
    unsigned long *masks = (unsigned long *)D_000001E8;
    interrupts[1] &= ~masks[counter & 0xFFFF];
    return 1;
}
```

File: `build/stoprcnt-solve/sdk_long_types.c`.

On this PSX ABI, `long` and `unsigned long` are 32-bit. These spellings were tested to remove a signature/type premise, not as a matching trick. They produced the same baseline program as the ordinary project aliases. Equal width/code generation should not be confused with the distinct C types being universally interchangeable under every aliasing rule.

## 5. What “macro” means in this investigation

There is no hidden C macro implementing this candidate. The relevant macro is **compiler-generated assembler shorthand**.

The actual native cc1 assembly contains:

```asm
lw $2,D_000001E8($4)
```

A basic MIPS `lw` encodes a signed displacement and one base register. It cannot directly encode a complete symbolic address plus another register. This extended form therefore requires expansion. In the production pipeline the expansion uses `$at`:

```asm
lui  at, HI(table)
addu at, at, index
lw   v0, LO(table)(at)
```

The user correctly noted that `$1/$at` is reserved as an assembler temporary. Its appearance is evidence of assembler-generated scratch usage in this candidate, not of a GCC allocation decision assigning an ordinary C local to register 1.

However, **normal use of `$at` is not itself an assembler error**. We know the candidate's compiler output and its expansion; we do not have the original compiler output. The original machine sequence could reflect a different compiler-emitted macro form, an explicit address sequence, a different compiler/backend/dialect/invocation, or another source/context distinction not yet recovered.

The earlier inference “our compiler emits this macro, therefore the original compiler emitted the same macro, therefore MASPSX is wrong” is unsupported. The original input must not be inferred from the candidate output.

## 6. Configured production toolchain

The current configuration is a candidate configuration, not a historical identification of every prebuilt SDK member.

| Component | Current setting |
|---|---|
| Compiler | GCC 2.7.2 PSX cc1 |
| Compiler SHA-256 | `0359379289db8e3904b8ed3b25b422ca631c8d71ab2f543d533c39ed2967764f` |
| Compiler source | `tools/vendor/gcc/2.7.2-psx/src/gcc`, pinned project source |
| MASPSX revision | `0249ed2752a100eed95e8b4124f94af859398ca9` |
| ASPSX compatibility mode | `--aspsx-version 2.80` |
| Assembler backend | Configured `mips-linux-gnu-as` |
| Compiler small-data setting | `-G0` |
| GAS flags for this member | `-march=r3000 -mtune=r3000 -EL -G0`, plus configured include directories |
| MASPSX protocol | `--aspsx-version 2.80 --use-comm-section --run-assembler` |

Production cc1 flags:

```text
-O2 -G0 -mips1 -mcpu=r3000 -funsigned-char -fpeephole
-ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm
-msoft-float -mgas -fgnu-linker -quiet
```

The configured analysis provider is `gcc-rtl`. The current runtime profile supplies 13 native dump stages and identifies `FIRST_PSEUDO_REGISTER` as 68. `.mach` is unavailable in this compiler. Pass ordering, reconstructed lifetime/allocation explanations and inverse-pass interpretations remain provisional where the required native evidence/replay is missing.

The cached alternative compiler used for diagnostic comparisons was GCC 2.95.2 PSX, SHA-256:

`2aa85925dfa10855107c78e29ec36965b953976a45b1a47fb68beb5a74096079`.

No compiler binary, source pin, assembler revision, or production flag was replaced during these experiments.

### Historical configuration records are not identification proof

Existing tracked identification documents retained obsolete 2.95.2 candidate metadata. A recorded change at `ee3df32` moved the configuration from 2.95.2/G8 to 2.7.2/G0 alongside a small Spu leaf integration. That history records a configuration choice; it does not identify the historical compiler for COUNTER.OBJ.

Likewise, SDK tool-distribution version strings and the provenance of SDK runtime source are not proof of the executable compiler version used to build every shipped object. Libraries may contain mixed or carried-over members.

## 7. Chronology and preparation

### 7.1 Earlier audit and cleanup

The user initially questioned repeated DeepSeek conclusions in the session named:

`2026-10-12T22-00-25-839Z_01a13221-9bef-718e-b55f-963939ea5120.jsonl`.

The broader audit found that three prior sessions had consumed existing experiment state after a ledger-only reset. It also found compiler-source coverage and matched-corpus eligibility defects, described in section 11 below. This established concrete tooling/state problems, **not a causal model-isolation proof**.

At the user's request, earlier generated experiments and 15 prior project sessions were removed, while code, inputs, configuration, dependencies and required native analysis support were preserved. Earlier deleted artifacts cannot now be presented as fresh reproducible measurements. This document does not fabricate an exhaustive listing of their discarded source variants.

Fresh matched-member receipts were subsequently restored through the production whole-TU oracle for the existing live accepted functions: 127 functions across 123 TUs at that point. This did not rewrite source or manufacture new C completions. Relevant surviving artifact: `build/match-state-sync/report.json`.

### 7.2 Fresh SetRCnt/StopRCnt session

The later session audited separately was:

`2026-10-13T03-37-33-593Z_01a13356-4299-7238-92f5-985ad3d1c9c2.jsonl`.

Its SetRCnt solution was genuinely gated at 03:40:47. The successful edit removed m2c-derived repeated temporary assignments and tested `arg2 & 0x1000` directly in the final condition. It was integrated and finalized at 39/39 through the actual terminal gate.

StopRCnt then received fresh source experiments. Its nine submissions did not merely rediscover a deleted old candidate directory. The audited session ended aborted, with no StopRCnt finalization or park.

The transcript audit and extraction receipt survive under:

`/tmp/psx-session-01a13356-audit/`.

The temporary path is session-local evidence and is not guaranteed to survive system cleanup.

### 7.3 m2c preparation and startup checks

A current installed-CLI m2c handoff preserved the existing draft as primary and refreshed its context/evidence. The draft was a verbose cast-based transcription of the same read/modify/write operation:

```c
s32 StopRCnt(s32 arg0) {
    (*(s32 *)((u8 *)D_000001E0 + 4)) =
        (*(s32 *)((u8 *)D_000001E0 + 4)) &
        ~D_000001E8[arg0 & 0xFFFF];
    return 1;
}
```

This rendering simplifies the saved draft's redundant outer cast. The exact saved draft is at:

`build/preparation/lib_f5b70e00e12530c5_0::StopRCnt/1791862949012-855230/draft.c`.

Refreshed handoff/context/evidence are under:

`build/preparation/lib_f5b70e00e12530c5_0::StopRCnt/1791863940513-869430/`.

Preparation reported compilation succeeded, comparison mismatching, no finalization, zero blockers and one unresolved fact. No SDK asm-template match or COP2 instruction was found.

Startup triage of the real natural candidate reported no findings and the zero target frame. Callee-truth found zero direct callees and no contradictory callee declarations. Later triage was rerun after the ET_REL fingerprint repair; that result is distinguished below.

## 8. Complete clean-C experiment inventory

All these experiments used the original ordered TU. None was integrated into the live StopRCnt fragment.

For the residual-objective measurements, use this common artifact prefix:

```text
build/pipelineReversal/lib_f5b70e00e12530c5_0::StopRCnt/objective/
```

The ledger is:

`build/experimentLedger/lib_f5b70e00e12530c5_0::StopRCnt.jsonl`.

It currently contains 19 source-measurement rows, including eight deduplicated initial rows and eleven subsequent C-form tests. The literal project-alias candidate was later measured through the direct whole-member diff and the fresh compatibility sweep, rather than added to that ledger.

### 8.1 Initial natural and pointer-spelling family

The fresh session submitted the initial natural function, then a four-source natural/index/RMW/mask batch, then four pointer spellings. The duplicate natural submission accounts for nine submissions but eight retained initial ledger rows.

| Source | Source-level change | Result | Measurement |
|---|---|---|---|
| `/tmp/StopRCnt_nat.c`; `build/stoprcnt_variants/v1_natural.c` | Direct `D_000001E0[1] &= ~D_000001E8[arg0 & 0xFFFF]` | Baseline 13-word program; three address-register differences | `measurement-gUxWYw/v1` |
| `build/stoprcnt_variants/v2_temp.c` | Save masked index in a local `s32 t` | Same baseline program | `measurement-zkVfLJ/v2` |
| `build/stoprcnt_variants/v3_rmw.c` | Spell `&=` as an explicit assignment and `&` expression | Same baseline program | `measurement-zkVfLJ/v3` |
| `build/stoprcnt_variants/v4_mask.c` | Save loaded mask in a `u32` local | Same baseline program | `measurement-zkVfLJ/v4` |
| `build/stoprcnt_variants/vp1.c` | Take `&D_000001E8[index]`, then dereference | Same baseline program | `measurement-818qo7/v1` |
| `build/stoprcnt_variants/vp2.c` | Form `D_000001E8 + index`, then dereference | Same baseline program | `measurement-818qo7/v2` |
| `build/stoprcnt_variants/vp3.c` | Inline `*(D_000001E8 + index)` | Same baseline program | `measurement-818qo7/v3` |
| `build/stoprcnt_variants/vp4.c` | Copy the table base to a local pointer | Same baseline program | `measurement-818qo7/v4` |

The original arguments in these files use `s32`; the final project-alias form uses `u32`. The low-halfword mask makes the signedness difference irrelevant to the observed code generation here.

Every retained initial row has the same recorded compiled-program output hash:

`913fafa8d9c18fff1404abccb38950e9061de96bbd6921fb1dafa6cb4ccd72e8`.

This is a ledger comparison-output identity, not a claim that ELF packaging/file hashes are identical.

### 8.2 Subsequent source families

The word counts below were checked against the saved **whole candidate objects' StopRCnt symbol extents** when preparing this document. They are not blindly copied from residual-projection counters.

| Source under `build/stoprcnt-solve/` | Hypothesis / actual change | Actual StopRCnt words | Outcome | Measurement |
|---|---|---:|---|---|
| `aggregate_word.c` | Load a one-word `struct MaskWord` array element, then use `.value` | 13 | Scalarized to the same baseline program | `measurement-iPtHcn/v1` |
| `volatile_mask.c` | Read the mask through `volatile u32 *` | 14 | Explicit address materialization; additional address operation and changed ordering; whole-member mismatch | `measurement-othdRs/v1` |
| `data_cluster.c` | View `&D_000001E0` as a record containing both pointers and the six masks | 13 | Different addressing/relocations; population/order differences; whole-member bytes and relocations mismatch | `measurement-dmli2X/v1` |
| `volatile_mmio.c` | Make the interrupt-register access volatile | 14 | Store no longer occupies the return delay slot; mask-address residual remains; whole-member mismatch | `measurement-c0og0h/v1` |
| `integer_address.c` | Cast table address to `u32`, add `(index << 2)`, cast back and load | 16 | Additional frame/temporary machinery and population differences; whole-member mismatch | `measurement-R7nae5/v1` |
| `table_in_counter_data.c` | Derive table pointer from `(u32 *)(&D_000001E4 + 1)` | 13 | Same baseline program | `measurement-BbW1QR/v1` |
| `demorgan.c` | Spell result as `~(mask | ~interrupts[1])` | 13 | Different order/register choices; unresolved address correspondence remains; whole-member mismatch | `measurement-I9rPoI/v1` |
| `builtin_mask_copy.c` | Copy the four-byte mask to a local with `__builtin_memcpy` | 17 | Stack/spill/frame machinery and multiple residual terms; whole-member mismatch | `measurement-xhBqvm/v1` |
| `register_locals.c` | Ordinary, **unpinned** C `register` locals for index, pointer and mask | 13 | Same baseline program; no hard-register assembly binding | `measurement-Kcl2td/v1` |
| `sdk_long_types.c` | Literal SDK `long(unsigned long)` types and corresponding pointer casts | 13 | Same baseline program | `measurement-gbrct4/v1` |
| `word_bitfield.c` | Read the mask through a record with a 32-bit unsigned bitfield | 13 | Same baseline program | `measurement-IFWHB2/v1` |
| `project_aliases.c` | Literal minimal `s32 StopRCnt(u32 counter)` shown to the user | 13 | Fresh whole-member 89/92 MISMATCH, same three words | Direct comparison and compatibility sweep, sections 4 and 16 |

The record views, integer-address form and volatility changes were experiments, not claims about the original source. No questionable storage-origin/type punning was promoted as a solution.

#### Native observation for the volatile-table experiment

The compiler emitted a sequence including:

```asm
andi a0, a0, 0xffff
la   v0, D_000001E8
sll  a0, a0, 2
addu a0, a0, v0
lw   a1, D_000001E0
lw   v0, 0(a0)
```

The `la` requires a high/low address materialization, giving an additional address operation relative to the desired three-instruction indexed access. Merely forcing a table read to be volatile did not recover the original compact form.

### 8.3 Important correction: projected counts are not actual instruction extents

Some existing objective records have misleading word denominators:

| Source | Archived projection display | Actual compiled StopRCnt extent |
|---|---:|---:|
| `volatile_mask.c` | `10/11` | 14 words |
| `data_cluster.c` | `8/11` | 13 words |
| `volatile_mmio.c` | `9/12` | 14 words |
| `integer_address.c` | `9/12` | 16 words |
| `builtin_mask_copy.c` | `4/13` | 17 words |

The target is still 13 words in every case. Those denominators are diagnostic projections, not evidence that the target shrank or that a near-exact result was obtained. The candidate object and whole-member oracle remain decisive. This reporting limitation has **not** been repaired as part of this notes-only task.

The source experiments that yielded the baseline output should not be rerun as new evidence without a changed compiler/context/operation premise. Conversely, their failure does not exhaust all clean C or every compiler invocation.

## 9. Compiler, residual and reconstruction diagnostics

### 9.1 Reverse-pipeline results

The natural candidate's reports explicitly state:

> Owner not established — incomplete value-web correspondence; consult the raw value definitions and selected native RTL before assigning a compiler pass.

The target reconstruction has 12 value webs versus 10 candidate webs, with target values 5 and 6 unpaired. Allocation is **ungraded**, not proven equal or proven wrong. The report's first-divergence entry mentions `greg`, but qualifies it with incomplete correspondence; it is not a licensed global-allocation causal verdict.

The pre-delay-slot round trip is missing, skipped or divergent. Pass ownership/source directions are provisional. `.mach` is unavailable for the actual compiler.

Some ledger/objective records show a zero key `[0,0,0,0]` while also recording `exact: false`, incomplete allocation coverage and a whole-TU mismatch. **A zero key is not an exact match or proof of allocation agreement.** The old resident tool rendering must not override the explicit qualifications in the current report.

Evidence:

`build/pipelineReversal/lib_f5b70e00e12530c5_0::StopRCnt/report.json`

and the individual immutable objective reports listed in section 8.

### 9.2 Native compiler tracing

Compiler tracing was actually run against C candidates, not only against the live assembly stub. The fresh DeepSeek trace selected `v1_natural.c`; the later trace selected `sdk_long_types.c`. The compiler supplied 13 native stages and seven surviving pre-reload pseudos after combine.

The critical directly observed native assembly is the extended indexed load:

`lw $2,D_000001E8($4)`.

Lifetime endpoints, hard-register hazards and reconstructed scheduler/allocation models remain subject to the report's native-evidence/replay caveats. A candidate trace cannot reconstruct the original compiler input merely by naming candidate pseudos.

Evidence:

`build/compilerTrace/lib_f5b70e00e12530c5_0::StopRCnt/report.json`.

### 9.3 Compiler-source inspection actually performed

The configured 2.7.2 source was inspected, including:

- `mips_move_1word`: a register loaded from SImode memory prints `lw %0,%1`; a register loaded from a symbol/constant address prints `la %0,%a1`.
- `mips.h` address-legitimacy rules: `PLUS(REG, CONSTANT_ADDRESS_P)` is accepted when the relevant debug/ABI conditions allow it. The source comment explicitly discusses permitting an assembler-expanded three-instruction indexed load rather than a compiler-generated four-instruction address calculation.
- `mips.md` `movsi_internal1`/`movsi_internal2`, which call `mips_move_1word`.
- Searches for ordinary HIGH/LO_SUM and `%hi`/`%lo` emission. The inspected ordinary emitter did not handle HIGH directly; a literal `%hi`/`%lo` sequence found in the MD was an ABI64 GP setup pattern, not an ordinary scalar-load solution.

The full `mips_move_1word` reading was saved temporarily at `/tmp/stoprcnt-move-source.txt`. The repaired source search covered 69 C/H/MD files in the fresh session; earlier zero-MD-coverage search output was a harness fault.

These observations explain why the natural candidate reaches an extended load under this configured compiler. **They are not a proof that all clean C, all contexts or all original compiler inputs are impossible.** Predicate/printer locations identified but not actually read are not presented here as completed evidence.

### 9.4 Matched-code retrieval and scratch census

The corrected corpus reported:

- 44 eligible ordinary clean-C matched functions;
- 25 represented functions / 68 indexed regions;
- 84 asm-macro exclusions;
- 14 stub exclusions in the eligibility inventory;
- a complete raw census over the 44 eligible ordinary-C functions;
- zero examples of the target's destination-as-scratch indexed-load relation.

There was no donor for this exact relationship. This is an honest coverage result, **not proof of unreachable C**. “127 matched functions” from earlier receipts is not equivalent to 127 ordinary-C witnesses of this assembler pattern. Sources that delegate work to assembly cannot validate its reconstruction from ordinary C.

### 9.5 Automatic reconstruction

The reconstruction engine returned `context-unresolved` immediately and compiled **zero candidates**. Its ET_REL symbolic-storage execution capability was not implemented for this target's symbolic accesses.

The target decode itself records 13 supported words, no back edge, no direct/indirect calls, and a store. The refusal is a capability limit, not a finding that StopRCnt is handwritten assembly or cannot be expressed in clean C.

Evidence:

`build/matchingReconstruction/lib_f5b70e00e12530c5_0::StopRCnt/result.json`

and `target.json` beside it.

No allocation/scheduler solver result, exhaustive clean-C grammar exhaustion, original-assembly-only classification or policy-exception approval was obtained for StopRCnt. Those must not be invented retrospectively.

## 10. Historical direct-GAS probes: observations and limits

These experiments were performed by the separately audited fresh DeepSeek session, **not rerun as a production replacement in the current investigation**.

1. A hand-authored GAS probe showed `lw $2,symbol($4)` using destination `$v0` as scratch. Destination-equals-index/base cases used `$at`.
2. An initial direct-GAS attempt on the real candidate full-TU cc1 assembly failed because `macro.inc` could not be found.
3. Retrying with the include path succeeded. The displayed StopRCnt function had the original 13 words and corresponding HI16/LO16 relocations, including `$v0` scratch.

The decisive limitation: the session displayed a StopRCnt objdump, **not a strict whole-member comparison of that bypass object**. It did not run real ASPSX on the same input. Therefore it did not establish:

- whole-member exactness of the bypass;
- the original ASPSX expansion in this geometry;
- the original compiler's input form;
- a MASPSX defect;
- impossibility of another clean-C candidate.

The session also read `test_expand_lw.py`. Its indexed input was `lw $2,ctlbuf($2)`, where destination equals index/base. StopRCnt's candidate is `lw $2,symbol($4)`, where they differ. That fixture does not settle the disputed geometry.

The audit locates these observations at transcript lines L189/L190 and L265/L266; the unsupported stronger conclusions appear at L267 and L279. No successful real-ASPSX execution, StopRCnt park or StopRCnt finalization appears in the transcript.

This historical evidence must not be silently promoted into an alternative oracle or a license to bypass MASPSX. The production pipeline remained unchanged.

## 11. Harness faults found, repairs made, and remaining limits

### 11.1 Earlier audit-contract repairs

The earlier audit found several ways tools could manufacture confidence from the wrong evidence:

- Compiler-source indexing/search did not include the MD files it claimed to cover.
- The donor corpus included assembly-backed macro sources as though they were ordinary C.
- Corpus representation counts did not make the real coverage obvious.
- Mutable measurement artifacts and stale/legacy ledger rendering could obscure which actual source/object had been measured.

The preserved uncommitted repairs cover compiler-source indexing/query coverage, AST-based corpus eligibility, a raw scratch census, immutable residual-measurement snapshots/manifests and ledger receipts, plus focused diagnostic regression tests and documentation. The focused earlier audit-contract tests reported 55 passing tests.

These repairs are **not** a complete implementation of source-to-object attribution for every assembler-expanded word.

### 11.2 Stale resident Pi tool wrappers

The resident wrappers in this long-running Pi session were older than the installed CLI implementation. Concrete symptoms included:

- `psx_m2c` rejecting `project.json` with `unsupported output.sourceLayout`;
- old ledger rendering presenting the zero-key interpretation without the current incomplete/ungraded qualifications.

Current measurements were therefore run through the installed script host rather than trusting the stale wrappers. No process was interrupted or Pi reloaded merely to refresh schemas.

### 11.3 Flag probe compiling the assembly stub

The intended flag-heuristic tool initially compiled StopRCnt's live `INCLUDE_ASM` placeholder as its primary source. It reported 13/13 across supported flag columns, while the real C advisory candidate remained 10/13. This was not validation of C or of the toolchain.

Repair:

- Added `--src` as a primary C-candidate selector.
- Bound source path/label/status/hash and conclusions to that actual candidate.
- Made an assembly stub fingerprint-only rather than a C matrix.
- Kept `--with-source` advisory-only; an advisory candidate cannot own a conclusion while the primary is a stub.
- Skipped advisory stubs, retained compiler rejection text and rejected unknown CLI arguments.
- Removed unjustified original-input/unreachable-C assertions from fingerprint prose.
- Forwarded optional `src` in the extension's flag-probe schema. The current resident schema still requires a later ordinary reload to expose that option; the installed CLI already supports it.

### 11.4 Inactive C branches misclassified as active assembly

`handsSymbolToAssembler` was changed to use the existing active-C walker. A disabled literal `#if 0` arm no longer turns a real C function into a stub merely because it contains an inactive `INCLUDE_ASM`. The added failing test was fixed rather than weakened.

### 11.5 ET_REL fingerprints silently missed by triage

Triage had scanned rendered assembly for literal `%hi/%lo`. The target's ET_REL listings can instead contain numeric operands and relocation footers, so the fingerprint was missed.

Repair:

- Added/exported `symbolicSelfClobberPairs`.
- Used symbolized original words from `targetWordsOf`.
- Accepted the register spellings used in those views.
- Removed stale foreign-project/unreachable-C claims.

After repair, actual-C triage reports one flag-fingerprint signal at original words **2–3**: the ordinary pointer load `lui a1` / `lw a1,...(a1)`. That is **not the disputed indexed table triple at words 4–6**, and is not a new explanation for it.

### 11.6 Validation and source-preservation results

The final focused run of flag-probe, triage, C-source-guard and diagnostic-candidate tests reported **64 passing, zero failing** tests. Nine new flag-probe regressions cover candidate/stub selection, active/inactive source and ET_REL fingerprint/conclusion rendering behavior.

A broader registration run reported **66 passing, one failing out of 67**. The failure was an existing unregistered `analysisSupport` CLI, absent from both the registered and explicitly unexposed inventories. It was not hidden or “fixed” by a bogus exclusion; that issue remains separate.

Evidence for the focused run: `/tmp/stoprcnt-heuristic-focused-tests.txt`.

Default-stub and advisory-only CLI behavior were explicitly checked after the fixes. The last normal flag-probe report was then restored to the real `sdk_long_types.c` candidate. Thirteen-file preservation snapshots matched, including the user's autoloop configuration, counter TU fragments, compiler, MASPSX and original member. Relevant files:

- `build/stoprcnt-config-heuristics/stub-flags.json`
- `build/stoprcnt-config-heuristics/advisory-flags.txt`
- `build/stoprcnt-config-heuristics/preservation-before.json`
- `build/stoprcnt-config-heuristics/preservation-after.json`

Remaining limits include incomplete inverse-pass/value-web attribution, the misleading projection extents documented in section 8.3, and absence of code-based compiler/ASPSX version inference in the library identification command. None is evidence that MASPSX itself is defective.

### 11.7 Why repeated agent conclusions were not independent confirmation

The audited reasoning repeatedly crossed the same evidentiary boundaries: candidate macro input became assumed original input; a function-only GAS listing became claimed whole-member exactness; repeated same-output C spellings became claimed clean-C impossibility; and incomplete/zero-key pass diagnostics became an allocator explanation. Inflated corpus eligibility and stale primary-source/tool rendering could reinforce those errors.

These are concrete attribution and context failures. They explain why repetition alone was not reassuring. They do not establish that every session followed the same causal path: the fresh session really did make new measurements, and its new GAS observations cannot be dismissed as old-object reuse.

## 12. Compiler and flag comparisons before the corrected heuristic-tool run

The first configuration comparisons used a bespoke build-only matrix, before the user correctly required using the existing heuristic tools. They are retained as measured evidence but are not mislabeled as heuristic-tool results.

Protocol:

- one freshly preprocessed original ordered whole TU;
- fixed `sdk_long_types.c` candidate;
- diagnostic cc1 binary/flag alternatives only;
- unchanged production MASPSX 2.80 -> GAS;
- the same whole-member relocated-object oracle;
- preservation snapshots before/after.

Two reports contain 18 rows total, including a repeated 2.7.2 baseline:

```text
build/stoprcnt-config-probe/6f47d478-1356-40c0-83d7-2c3d02095d3b/report.json
build/stoprcnt-config-probe/0e3c6d65-a5bb-4c63-9745-4a3824684ab9/report.json
```

Every compiling row was a whole-member MISMATCH. The table's StopRCnt word comparisons are raw function diagnostics, not relocation-complete acceptance scores or a search distance.

| Compiler | Diagnostic change | StopRCnt raw words agreeing / target 13 | Candidate function words | Whole-member outcome |
|---|---|---:|---:|---|
| 2.7.2 | Baseline O2/G0; repeated in both reports | 10 | 13 | Mismatch; baseline three words |
| 2.7.2 | `-mdebuga` (disable indexed symbolic-address acceptance) | 0 | 14 | Mismatch; different address form/order and member geometry |
| 2.95.2 | Baseline | 0 | 14 | Mismatch; neighboring C also differs |
| 2.95.2 | `-msplit-addresses` | 0 | 14 | Same result as that compiler's baseline |
| 2.95.2 | `-mno-split-addresses` | 10 | 13 | Baseline-like Stop residual; neighboring C/member still mismatch |
| 2.7.2 | `-O1` | 1 | 15 | Mismatch |
| 2.7.2 | `-O3` | 10 | 13 | Same baseline result |
| 2.7.2 | `-fno-schedule-insns` | 5 | 13 | Mismatch; different order/register choices |
| 2.7.2 | `-fno-schedule-insns2` | 8 | 13 | Mismatch; return/store ordering changes |
| 2.7.2 | Both scheduling passes disabled | 0 | 15 | Mismatch |
| 2.7.2 | `-fno-peephole` | 10 | 13 | Same baseline result |
| 2.7.2 | `-fno-function-cse` | 10 | 13 | Same baseline result |
| 2.7.2 | `-mno-gas` | — | — | Compiler rejects option `no-gas` |
| 2.7.2 | `-mno-gnu-linker` | — | — | Compiler rejects option `no-gnu-linker` |
| 2.7.2 | cc1 `-G8` instead of G0 | 10 | 13 | Mismatch; relocation/symbol population also differs |
| 2.95.2 | Split addresses, both scheduling passes disabled | 0 | 16 | Mismatch |
| 2.95.2 | Unsplit addresses, both scheduling passes disabled | 0 | 15 | Mismatch |

For the G8 experiment, the changed flag was the **compiler** threshold. The assembler flags remained the configured production flags; this was not a coordinated replacement of the whole pipeline's small-data settings. Its raw 10/13 count therefore does not mean it reproduced the same relocation semantics.

At the 2.7.2 baseline, the raw diagnostics for the exact neighbors were SetRCnt 39/39, GetRCnt 14/14 and StartRCnt 12/12. ResetRCnt's raw 13/14 display includes the inferred padding/size convention; it was not an additional semantic whole-member difference. The strict baseline difference remained StopRCnt's three words.

**Scope of conclusion:** neither cached compiler version nor these selected flag alternatives fixed this candidate. This is not a proof of the historical compiler version or an exhaustive compiler/flag cross-product closure.

## 13. Results from the intended identification and flag-heuristic tools

### 13.1 Identification command

The installed `tools/diagnostics/identifyToolchain.ts --json` explicitly returned:

> undetermined — ELF metadata does not identify the historical compiler/flags.

The ELF/ar branch inventories target members and separates configured choices, but does not run a code-based compiler-version or ASPSX-version classifier. It did **not** validate GCC 2.7.2 or ASPSX mode 2.80.

Evidence: `build/stoprcnt-config-heuristics/identify.json`.

### 13.2 Corrected flag matrix on actual C

Primary source: `build/stoprcnt-solve/sdk_long_types.c`.

Source SHA-256:

`c8b8aba8779ed76a61b059b16f1ca285f6d5df90077bf30768ebb0ed9fcc7af7`.

| Tool matrix column | Reported masked instruction agreement | Reported function extent | Outcome |
|---|---:|---:|---|
| Baseline | 10/13 | 13 | No remedy |
| `-fno-gcse` | 10/13 | 13 | Tied |
| Both scheduling passes disabled | 0/13 | 15 | Worse for this candidate |
| `-fno-schedule-insns2` | 8/13 | 13 | Worse for this candidate |
| `-fno-gcse` plus both scheduling passes disabled | 0/13 | 15 | Worse for this candidate |
| `-fno-rerun-cse-after-loop` | 10/13 | 13 | Tied |
| `-mno-split-addresses` | — | — | Rejected by current cc1: `Invalid option no-split-addresses` |
| `-fno-cse-follow-jumps` | 10/13 | 13 | Tied |
| `-fno-cse-skip-blocks` | 10/13 | 13 | Tied |
| Both CSE follow/skip flags | 10/13 | 13 | Tied |

The actual tool conclusion is **inconclusive**, with no dominant flag rows. Masked word agreement is not the whole-member verdict. A tied accepted switch is not proof that the compiler implemented a distinct pass or that every flag/source interaction has been eliminated. A rejected switch is unavailable evidence, not a refutation of the configuration hypothesis.

Evidence:

- `build/stoprcnt-config-heuristics/flags.txt`: initial stub-primary/advisory observation.
- `build/stoprcnt-config-heuristics/candidate-flags.txt`: corrected actual-C result.
- `build/flagProbe/lib_f5b70e00e12530c5_0::StopRCnt/report.json`: last primary-C report.
- `build/stoprcnt-config-heuristics/triage.json`: corrected original-word triage signal.

## 14. Other-project ASPSX notes inspected

At the user's direction, the following BTN documents and their referenced implementation were read:

- `../btn-decompilation/notes/toolchain-version-detection.md`
- `../btn-decompilation/notes/adr-0001-symbol-addressing-at-the-assembler-boundary.md`
- `../btn-decompilation/notes/maspsx-issue.md`
- `../btn-decompilation/notes/maspsx-issue2.md`
- `../btn-decompilation/notes/maspsx-issue3.md`
- relevant portions of `tools-directory-structure.md` and `potentially-useful-tools.md`
- `../btn-decompilation/plans/aspsx-same-input-differential.md`
- the vendor ASPSX test catalog, including `test_expand_li.py`, `test_la.py`, `test_sltu_at.py`, `test_div.py`, `test_v0_at.py` and `test_addu_at.py`.

The reusable version signals are small-constant `li`, div overflow traps, negative-immediate `sltu`, extra nops at `$at` expansions, HI/LO gap enforcement, and GP-relative `la`.

Relevant distinctions from those notes:

1. BTN's 2.77 -> 2.80 refinement came from GP-relative `la` evidence in **BTN's** original code. That is not evidence that every supplied SDK object used that release.
2. ADR-0001 identifies a pipeline-configuration mistake involving `--dont-force-G0`; it explicitly says that MASPSX already implemented the correct small-data authority rule. No analogous flag was silently enabled here.
3. `maspsx-issue3.md` retracts the supposed forward delay-slot-fill defect. Correct C made cc1 fill the slot, and the local patch was removed. Its historical body must not be read as current status.
4. Older issue proposals and foreign-game observations are hypotheses/history, not fresh StopRCnt evidence.
5. The same-input differential is described as a proposed supported diagnostic. The inspected ordinary toolchain-profile commands were SDK/vendor/configuration detectors, not automated ASPSX-mode sweeps of this library.
6. The vendor ASPSX catalog can run period assemblers through Wine/dosemu, but those tests were **read, not executed or downloaded** for this task.

The user also supplied MIPS documentation explaining `$at` and pseudo-instruction expansion. That clarified the compiler-to-assembler boundary, not a hidden C macro or an assembler malfunction.

## 15. Original-byte ASPSX version inference actually performed

This scan was requested explicitly after the gap in the identification command was acknowledged.

### 15.1 Scope and method

- All 2,224 configured converted-original ELF members were read through the existing relocatable-object/library helpers.
- 2,188 members have executable bytes, totaling 1,243,796 bytes.
- Six deferred original members outside the selected convertible inputs were not scanned; see `configs/deferred-sdk-objects.json`.
- The scan used original words, not candidate objects or a compiler-generated probe.
- Immediate-pattern counts excluded relocated words. GP-address evidence retained relocation information. Exact div and `$at` templates checked the relevant instruction/register relationships.
- Each witness retains its member/input, section offset, function label where available and raw words. Original function extents may be inferred.
- No homogeneous assembler version was assumed across different members.

The decoder reported 19,373 words outside its modeled integer vocabulary across these executable sections. Executable sections may also contain handwritten code or padding. The census is bounded pattern evidence, not an origin proof for every instruction or a full-program control-flow proof.

Artifacts:

```text
build/aspsx-version-fingerprints/report.json
build/aspsx-version-fingerprints/report.md
```

### 15.2 Findings by signal

| Signal | Original-word observations | Licensed interpretation |
|---|---|---|
| Small-positive constant loads | 5,817 `addiu`; zero `ori` for values 1..0x7FFF | Supports >=2.56 behavior **if originating from `li` expansion** |
| Large unsigned constant control | 293 `ori` loads for values >=0x8000 | Correctly separated from the small-positive discriminator |
| Signed-div overflow | 878 exact `break` templates; zero matching `tge` templates | Against 2.05/2.08 behavior **if originating from the div macro**; not a unique later release |
| Negative-immediate unsigned comparison | Zero distinguishing direct negative `sltiu`; zero load-negative-constant-to-`at` then `sltu` cases | No 2.70-class bound available |
| Ordinary nonnegative `sltiu` | 420 | Non-discriminating; must not be counted as proof of a newer assembler |
| Extra nop before `$at` store expansion | 29 qualified HI16/LO16 templates without the extra nop; zero with it | Supports >=2.30 behavior under macro-origin premise |
| HI/LO gap enforcement | 2,445 qualifying short linear reader-to-writer windows with two intervening instructions; zero with fewer | Consistent with >=2.30; assembler insertion is not independently proven |
| GP-relative address materialization / `la` | Zero GP-based `addiu` address-materialization witnesses | No >=2.80 witness; absence is **not** proof of <2.80 |

For the two-instruction HI/LO windows: 992 contain no nop, 1,293 contain one nop, and 160 contain two nops. Useful independent instructions can satisfy the hazard gap; not every qualifying window proves assembler nop insertion.

The report's per-member conditional lower bounds are:

- 1,117 members: >=2.56 fingerprint;
- 27 members: >=2.30 fingerprint without the stronger small-constant witness;
- 1,080 members: undetermined, including members with no relevant code.

These counts are not a vote for one historical release across the whole SDK.

### 15.3 Important refinement to the simplified decision tree

The distinguishing `sltu` fixture uses a **negative immediate**. An ordinary `sltiu reg,reg,2`, such as SetRCnt's, can already be a basic instruction emitted by the compiler and does not prove a newer macro-expansion strategy.

Also, the stored vendor fixture expects direct negative `sltiu` at 2.67, while the note and pinned wrapper use a 2.70 cutoff. No such distinguishing target site was found, so this catalog/cutoff discrepancy was not used to force an incorrect bound.

The original compiler input remains unknown for `li`, `div` and `la`, too. An explicitly supplied basic instruction can reproduce a fingerprint without the assembler having selected that expansion. The report therefore labels its bounds as conditional rather than unique historical identification.

### 15.4 COUNTER.OBJ-specific result

COUNTER.OBJ has seven small-positive `addiu` loads and zero corresponding `ori` loads:

- SetRCnt: constants 72, 73, 2, 584 and 1;
- StopRCnt: constant 1;
- ResetRCnt: constant 1.

StopRCnt's witness is `0x24020001` at `.text+0x12C`.

There is no div, HI/LO or GP-la discriminating site in this member. Its sole `sltiu` is SetRCnt's positive-immediate comparison with 2. Thus these signals leave **2.56–2.69, 2.70–2.79 and >=2.80** indistinguishable for this member.

**Configured:** MASPSX in ASPSX 2.80 compatibility mode.

**Inferred from COUNTER.OBJ:** conditional >=2.56 behavior class; exact historical assembler release undetermined.

### 15.5 Native original LNK provenance crosscheck

To ensure the important constant-load fingerprint was not merely a conversion artifact, COUNTER.OBJ was extracted read-only from the supplied native LIBAPI.LIB by its recorded ordinal and hashes.

An initial attempt to use the vendor ASPSX catalog's small `read_text_section` helper failed on exported-symbol record 12; that helper handles only a limited LNK record subset. No result relied on it.

The already configured PCSX-Redux parser was then run in **parse-only verbose mode**, with no ELF conversion or assembler invocation. The extracted original `.text` is 368 bytes, exactly the converted ELF's extent. All unrelocated words agree. Eight words differ only at existing relocation sites, reflecting relocated encoded addends in the converted representation. The StopRCnt return-constant word agrees directly.

Native/converted differing `.text` word offsets are:

`0x1C, 0x84, 0xB0, 0xE0, 0xEC, 0x110, 0x11C, 0x14C`.

This is a word-provenance check, not a claim that native LNK and ELF packaging/relocation formats are byte-identical.

Artifacts:

- `build/aspsx-version-fingerprints/counter-lnk-provenance.json`
- `build/aspsx-version-fingerprints/counter-lnk-parser.txt`
- `build/aspsx-version-fingerprints/counter.original.obj`

## 16. Exhaustive effective ASPSX-compatibility sweep for the current candidate

The user subsequently requested trying every MASPSX version. In context this meant **ASPSX compatibility versions of the pinned MASPSX**, not changing MASPSX Git revisions or downloading historical assembler binaries.

### 16.1 Domain and coverage

MASPSX accepts numeric `--aspsx-version` settings, not a finite enum of release binaries. The experiment tested:

- every hundredth setting from **1.00 through 2.99**: 200 settings;
- the **unversioned default**: one additional setting;
- consequently every documented catalog release: 1.05, 1.07, 2.05, 2.08, 2.21, 2.30, 2.34, 2.56, 2.67, 2.77, 2.79, 2.81 and 2.86;
- the production setting 2.80;
- all intermediate boundaries in the pinned wrapper.

Some numeric settings are not claimed to be actual historical releases. They cover the implementation's behavior branches.

The wrapper's relevant boundaries are:

- `1.10 < version < 2.10`: alternate div trap setting;
- `<2.30`: extra nop at expansion, old address-addition behavior, no newer HI/LO gap setting;
- `>=2.50`: different immediate-expansion setting;
- `>=2.70`: different `sltu` and GP-symbol-offset settings;
- `>=2.80`: GP-relative `la` setting.

The sweep reaches **all six distinct version-state combinations** exposed by that wrapper. Values outside the tested numeric interval repeat the edge states for these comparisons. This is exhaustive over those **version states with the other production options fixed**, not over all flags, all C sources, all compilers, MASPSX revisions or historical ASPSX binaries.

### 16.2 Measurement protocol and replay gate

1. Compile the literal `project_aliases.c` candidate freshly through `measureLibraryFunction`, using the original ordered production TU.
2. Preserve its full preprocessed input and **full TU cc1 assembly**, not the function-local projected `.s`.
3. Feed that same unmodified full-TU assembly to the pinned MASPSX -> configured GAS for every row, changing only the version argument.
4. Compare every resulting whole member with the same original whole-member oracle.
5. Keep per-version command lines, stderr/stdout, object hashes, normalized program identities and explanatory function projections.
6. Capture post-MASPSX assembly for documented releases, production 2.80 and the unversioned default.
7. Check that the 2.80 sweep path reproduces the freshly compiled production candidate through the whole-member oracle.
8. Check preservation hashes of production inputs, TU fragments, source candidate, compiler and MASPSX sources before/after.

The 2.80 replay is **MATCH against the production candidate**, 92/92 words. It is **not MATCH against the original target**. This replay licenses the diagnostic assembly path; it does not manufacture a solution.

### 16.3 Results

All 201 settings assembled successfully. There were six option-state combinations but only three distinct whole-member program outputs for this TU.

| Settings | Number of settings | StopRCnt words | Whole-member agreement / original 92 words | Result |
|---|---:|---:|---:|---|
| 1.00–2.29 | 130 | 14 | 53/92; candidate member has 96 words | Mismatch; additional address operation/other differences and shifted member geometry |
| 2.30–2.49, plus unversioned default | 21 | 13 | 83/92 | Mismatch; address triple plus small-constant expansion differences |
| 2.50–2.99 | 50 | 13 | 89/92 | Same baseline three-word mismatch |

**Every row uses `$at` for the indexed mask address. No row is an original whole-member match.**

In the middle group, StopRCnt's differing relative offsets are `0x10`, `0x14`, `0x18` and `0x28`; the last is the small-positive return-constant expansion. In the newest group, only `0x10`, `0x14`, `0x18` differ: the address triple.

No production input changed. The sweep's verdict is tightly scoped:

> Selecting another ASPSX compatibility version cannot fix this exact candidate's current full-TU GCC output through this pinned MASPSX/GAS pipeline with all other options fixed.

It does not identify the original assembler version, prove a MASPSX defect, establish that all clean C is impossible, or eliminate a different compiler/backend/dialect/invocation/source context.

### 16.4 Artifacts

```text
build/stoprcnt-aspsx-sweep/run.ts
build/stoprcnt-aspsx-sweep/latest.json
build/stoprcnt-aspsx-sweep/3273aa03-55e6-47e7-904d-69acb558a5c1/report.json
```

The run directory also contains fixed full-TU `.i`/`.s` input and one directory per setting, with the candidate object, streams and row report. The script is a build-only diagnostic, not production configuration or a new acceptance mechanism.

## 17. What is settled, what is not, and what should not be repeated

### Settled observations

- The original and baseline candidate differ in three precisely identified address-register instructions.
- The minimal C reproduces the intended operations and all other baseline instructions without an extra frame, call, guard or loop.
- The current compiler supplies an extended indexed load; candidate `$at` appears during expansion, not from an ordinary C variable assignment.
- The natural/pointer/RMW/local/type spelling families listed above repeatedly produce the same program.
- The selected compiler/flag rows did not solve the whole member.
- Original fingerprints do not identify 2.80 specifically.
- Every effective version-dependent state of the pinned MASPSX has now been exercised for the fixed current input; none replaces this scratch with `$v0`.
- The ordinary-C donor corpus has no represented example of this exact destination-scratch relationship.
- The reconstruction engine did not search this symbolic-storage domain.

### Unresolved questions

- Which compiler executable/backend/driver and assembler dialect were actually used for COUNTER.OBJ?
- What exact assembly did that compiler emit for the indexed load?
- Was it a pseudo-instruction or an explicit sequence, and under what invocation/context?
- Is there an evidence-backed source/declaration/operation distinction not represented by the current straightforward C?
- How should the harness represent and attribute assembler-expanded address webs without treating incomplete inverse-pass state as allocator evidence?

A correct MASPSX paired with different compiler-generated input conventions can still produce a mismatch with a historical object. That is the user's tooling-mismatch hypothesis and remains a reasonable investigation direction, **not an established diagnosis**.

### Claims not licensed by the evidence

- “MASPSX is defective.”
- “Original ASPSX must have seen our exact `lw` macro.”
- “All clean-C forms are impossible.”
- “The original assembler was exactly 2.80.”
- “127 matched receipts validate this specific pattern in 127 ordinary-C functions.”
- “A displayed direct-GAS StopRCnt objdump proves an exact whole member.”
- “A zero staged residual key proves allocation agreement or exactness.”
- “An unavailable flag rejects the entire configuration hypothesis.”

### Reopening criteria for measured directions

| Direction | Current closure | What would make it a different experiment |
|---|---|---|
| Natural pointer/index/RMW spellings | Same output under measured context | Changed verified declarations/context/compiler input or a genuinely different operation form |
| Literal SDK versus project scalar spellings | Same output | Independent evidence that another type/layout/invocation changes the address form |
| Selected compiler/flag rows | No winner for fixed SDK-type candidate | A new compiler/backend/driver candidate or an untested meaningful flag/source interaction |
| Compatibility version alone | No winner across all six states for fixed full-TU input | Different compiler-generated assembly, another production option, or an independently justified different toolchain revision; not a repeat of a documented version already covered |
| Allocation/scheduler explanation | Not established; missing target webs | Complete, replay-supported correspondence or explicit evidence licensing ownership |
| Automatic reconstruction | Zero candidates, capability refusal | ET_REL symbolic-storage execution support or genuinely resolved context |

None of these is an ordinary-difficulty park or an unconditional impossibility proof.

## 18. Reproduction and evidence index

### Current installed CLI invocation

The current long-lived resident Pi wrappers can be stale. The installed CLI form used for trustworthy diagnostics is:

```bash
HOST=/home/dave/Documents/code/psx-decompilation-harness/tools/lib/scriptHost.ts
LOADER=/home/dave/Documents/code/psx-decompilation-harness/node_modules/tsx/dist/loader.mjs

node --import "$LOADER" "$HOST" tools/agent/diffFunc.ts \
  --project "$PWD" 'lib_f5b70e00e12530c5_0::StopRCnt' \
  --src build/stoprcnt-solve/project_aliases.c
```

The current primary-C flag-probe form is:

```bash
node --import "$LOADER" "$HOST" tools/agent/flagProbe.ts \
  --project "$PWD" 'lib_f5b70e00e12530c5_0::StopRCnt' \
  --src build/stoprcnt-solve/sdk_long_types.c
```

The saved compatibility sweep can be reproduced explicitly with:

```bash
node --import "$LOADER" build/stoprcnt-aspsx-sweep/run.ts
```

It generates a new immutable run directory and does not change production flags. These are reproduction instructions, **not commands automatically run by this documentation task**. Do not invent nonexistent `finalizeFunction.ts`/`buildCallGraph.ts` entrypoints; finalization is owned by the actual extension/shared gate.

### Principal artifact map

| Evidence | Location |
|---|---|
| Original TU and source fragments | `src/libraries/libapi/72-counter/` |
| Original converted input | `library-input/redux/libapi/72-counter.o` |
| Materialized original object | `build/libraries/originals/lib_f5b70e00e12530c5_0/f9696b5b2525f5948c2e265374583b643e5fe7484870ce81a921db325f1c6c2b.o` |
| Original nonmatching/disassembly views | `build/libraries/nonmatchings/lib_f5b70e00e12530c5_0/`; `build/libraries/disassembly/lib_f5b70e00e12530c5_0/member.s` |
| Prepared source/context | Two preparation directories in section 7.3 |
| Initial C variants | `build/stoprcnt_variants/` |
| Subsequent C variants | `build/stoprcnt-solve/` |
| Ledger and immutable source snapshots | `build/experimentLedger/lib_f5b70e00e12530c5_0::StopRCnt.jsonl`; `build/experimentLedger/sources/` |
| Residual reports | Objective directories in section 8; root reverse-pipeline report in section 9 |
| Compiler trace | `build/compilerTrace/lib_f5b70e00e12530c5_0::StopRCnt/report.json` |
| Automatic reconstruction refusal | `build/matchingReconstruction/lib_f5b70e00e12530c5_0::StopRCnt/result.json` |
| Manual compiler/flag matrices | Two UUID reports in section 12 |
| Heuristic-tool observations/repair checks | `build/stoprcnt-config-heuristics/` |
| Last primary-C flag report | `build/flagProbe/lib_f5b70e00e12530c5_0::StopRCnt/report.json` |
| Original-word fingerprints | `build/aspsx-version-fingerprints/` |
| Native COUNTER.OBJ word provenance | `build/aspsx-version-fingerprints/counter-lnk-provenance.json` |
| 201-setting compatibility sweep | `build/stoprcnt-aspsx-sweep/latest.json` and its referenced run directory |
| Fresh DeepSeek transcript audit | `/tmp/psx-session-01a13356-audit/` (temporary) |
| Focused repair tests | `/tmp/stoprcnt-heuristic-focused-tests.txt` (temporary) |

`build/` and `/tmp/` evidence is generated/session-local and can be deleted by cleanup. This note preserves the substantive findings and bounds, but does not pretend that deleted artifacts remain replayable or that a later file at the same path necessarily has the same measured identity. Prefer immutable row manifests and stored source/object hashes when resuming.

**Historical final status:** unmatched StopRCnt; ordinary C semantics recovered; exact historical compiler input/tooling relationship unresolved; compatibility-version-only remedy measured and rejected for the fixed input; no assembler-defect finding or unconditional clean-C impossibility claim.

## 19. Resolution: configured GNU assembler backend (2026-10-13)

Implemented `plans/configurable-assembler-backend.md` in the sibling harness
and adopted direct GAS here. MASPSX and its pin are unchanged. For the original
indexed load, GNU as uses the destination as scratch when destination != index;
ASPSX/MASPSX uses $at. Modern GAS's move encoding is reconciled by the closed,
compiler-only `move-addu` rewrite. GAS retains default reorder optimization;
no `-O1` override was added.

The minimal C from §1 is integrated in
`src/libraries/libapi/72-counter/StopRCnt.c`, without rewriting neighbors or
storage. Its whole COUNTER member matches **92/92 words**, and the function
matches **13/13**. ResetRCnt and member data remain original assembly backlog.

The official finalization implementation passed exact diff, the active plus
previously accepted member build, scope, source policy and context publication.
The loaded Pi tool retained an older in-process project-schema module and
rejected the existing `tu-directory` layout before reaching the gate. Running
the same implementation in a fresh runtime resolved that tooling-staleness
issue without changing configuration semantics or weakening the gate.

Reversal now reports equal populations at every waypoint: **machine 13,
dbr 10, mach 10, greg/lreg 9**. Allocation correspondence is `complete: true`,
with empty target/candidate unpaired lists. The address webs formerly described
in §9.1 no longer remain unpaired: indexed-triple folding's expected effect was
measured, not assumed. The unavailable pre-delay-slot .mach replay remains
explicitly provisional; byte acceptance comes from the whole-member oracle.

As a separate integration, SetInitPadFlag's ordinary global assignment passed
its official gate: **164/164 whole-member words**, **3/3 function words**. Its
GAS listing witnesses `lui at / jr ra / sw a0,0(at)`. MASPSX and GAS -O1 cannot
supply that reorder-mode macro swap.

All **123** previously verified members were re-verified successfully. Both new
functions belong to that existing set through already-matched neighbors; this
is not a claim that all 2,224 members are reconstructed or verified. There were
no assembler warnings in **125** retained GAS production receipts. Both new
functions have rewritten-input/listing receipts, with listing objects
byte-identical to production objects.

Evidence under `build/assembler-backend-evidence/`:
- `configured-identification.json`: indexed-load and native packaging census,
  with explicit incomplete/ambiguous entries.
- `reverification.log`, `prior-verifications.json`: the 123-member guard.
- `StopRCnt.finalization.json`, `SetInitPadFlag.finalization.json`: separate
  official gate results and context publication.
- `expansion-captures.jsonlog`, `assembler-warnings.json`: input/listing/object
  hash receipts and empty warning streams.
- `build/pipelineReversal/lib_f5b70e00e12530c5_0::StopRCnt/report.json`: exact
  reversal with complete web correspondence.

Former source/allocator/flag no-go results are conditional on their old MASPSX
acceptance path. They do not establish clean-C impossibility. GCC 2.7.2 remains
the configured candidate; this resolution identifies an assembler family, not
the historical compiler or a particular GNU as release.
