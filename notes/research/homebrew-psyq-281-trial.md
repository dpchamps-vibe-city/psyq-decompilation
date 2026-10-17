# Homebrew Psy-Q GCC 2.8.1: controlled whole-member trial

Date: 2026-10-17. User authorized the proposed compiler trial. This is a diagnostic comparison, not a production compiler migration or historical compiler identification. No live source, flags, compiler selection, verification receipt, or policy approval was changed by the trial.

## Compiler identities

| Role | Identity |
| --- | --- |
| Production baseline | `build/dependencies/compiler/gcc-2.7.2-psx/cc1`, SHA-256 `0359379289db8e3904b8ed3b25b422ca631c8d71ab2f543d533c39ed2967764f` |
| Alternative | `../btn-decompilation/tools/vendor/homebrew-psyq/build/psyq-4.4_old-school/gcc-2.8.1/cc1`, SHA-256 `61fd8afeeeb3f86028eabf222aa6ceda5072924f1caa4553d5570a700616cbfd` |
| Alternative banner | `GNU C version 2.8.1, Psy-Q 4.4, Homebrew Psy-Q 0.2.0 (mips-psx) compiled by GNU C version 2.7.2.3.` |
| Alternative checkout | `8b01a6e8746e3fe7ce1cc45f5992ef71b5d62c1f` |
| Public upstream parent | `bdee891005a0aec6bf6fe40e504cf068ebf38caf` |

The local checkout is clean. Its one commit beyond the public parent adds two static-build shell scripts (41 lines), not optimizer/backend changes. Neither compiler was patched or rebuilt during this trial. The alternative's local executable identity is recorded independently of its checkout revision; this experiment does not establish a fresh reproducible source-to-binary build.

## Design and artifacts

Runner: `build/sn281-trial/compare.mts`.

Run from the project root:

```sh
LOADER=$(node -p "require.resolve('tsx', {paths:['/home/dave/Documents/code/psx-decompilation-harness']})")
node --import "$LOADER" build/sn281-trial/compare.mts
node --import "$LOADER" build/sn281-trial/compare.mts --no-split
node --import "$LOADER" build/sn281-trial/compare.mts --guarded --no-split
node --import "$LOADER" build/sn281-trial/compare.mts --no-cse-loop --no-split
```

Selection is every existing verification record with nonempty completed C functions: 137 C-bearing original members across 15 library directories. 121 are fully reconstructed C; 16 still contain original assembly backlog. Each baseline is freshly compiled from current live files, not accepted on the strength of an old receipt. Both compilers receive identical whole-TU `.i` bytes and logical filenames, preserving function order, declarations, neighboring code/data and current per-TU overrides. The second arm changes only the alternative's `-mno-split-addresses` setting.

Assembly uses the original member's configured production backend/profile and the harness's shared assembler implementation. Verification invokes the existing complete `compareRelocatableObjects` oracle: program sections, exact bytes including encoded relocation addends, exports/imports/storage and symbolic relocation relationships. No masked or function-only comparison substitutes for this gate. No acceptance records are published.

Reports retain original hashes, source-fragment hashes, preprocessed hashes, effective flags, compiler/assembler commands, diagnostics, objects and comparisons:

- `build/sn281-trial/report.json`: same explicit flags, alternative target defaults unchanged.
- `build/sn281-trial/no-split-addresses/report.json`: alternative with `-mno-split-addresses`.
- Per-member subdirectories retain raw output and complete comparison reports.
- Guarded copy-helper candidate: `allocator-guarded-candidate-report.json` under each arm.
- Loop-boundary removal candidate: `no-split-addresses/realloc3-no-cse-loop-report.json`.
- Raw tail localization only: `build/sn281-trial/copy-tail-localization.json`.

### Debug metadata adapter

The alternative repeatedly emits `.file 1` for different included source files. Modern GAS rejects this. The diagnostic adapter comments out only conflicting `.file` metadata rows, outside handwritten `#APP` regions, retaining the raw compiler output. It changes no instruction, label, storage or relocation directive. The same adapter is inspected on baseline output; any actual baseline changes require an independent whole-program-object comparison before continuing. This is debug compatibility handling, not an instruction-repair pass and not a production integration.

## Results

| Compiler/settings | Exact whole members / 137 | Exact fully-C members / 121 |
| --- | ---: | ---: |
| Existing GCC 2.7.2 | 137 | 121 |
| Homebrew 2.8.1, same explicit argv | 115 | 110 |
| Homebrew 2.8.1 plus `-mno-split-addresses` | 124 | 113 |

All selected members compile and assemble after the debug metadata handling; no rejecting C diagnostics were detected in either corpus arm. Whole-member successes with assembly-backed neighbors are not claims that those neighbors were compiled from C.

The corpus is heavily biased toward simple code and the current compiler: 109 of the 121 fully-C members have at most eight target words. Among the remaining twelve fully-C members, unchanged Homebrew defaults match three and the no-split arm matches five. These counts are compatibility measurements of existing C, not a statistical estimate of the historical compiler or proof that other compilers cannot reconstruct these members.

### A significant correction to the earlier switch rationale

`SpuGetTransferStartAddr` is a whole-member exact match under Homebrew 2.8.1 **with `-mno-split-addresses`**. It fails with Homebrew's default split-address setting.

The baseline emits unsplit global-load macros for this source; Homebrew defaults to split HI/LO address formation. Consequently the match cited by the 2026-10-11 global GCC 2.7.2 adoption commit is **not a discriminator uniquely selecting version 2.7.2**. This does not establish that the whole switch had no other justification.

### Remaining incompatibilities in the no-split arm

Thirteen current members no longer match unchanged. The eight fully-C cases are:

- `libapi/14-c160.o` (`_boot`)
- `libapi/77-padstop.o`
- `libapi/79-malloc2.o`
- `libapi/81-realloc2.o`
- `libapi/82-calloc2.o`
- `libapi/85-malloc3.o`
- `libmcx/2-mcxcmd3.o`
- `libsnd/216-vs_vtc.o`

The five mixed cases are `libapi/72-counter.o`, `73-sc2b.o`, `75-first.o`, `76-pad.o`, and `libsnd/51-ssclose.o`. Reports distinguish byte, size, relocation and exported-offset differences. The sources were not rewritten to compensate. The source-compatibility failures do not historically exclude Homebrew's compiler family.

## Allocator-specific checks

The current `87-realloc3` TU, with its copy helper still assembly-backed, matches completely under both production 2.7.2 and the no-split 2.8.1 arm. Thus `realloc3` and the rollback helper survive that counterfactual unchanged. The original section still has 108 words in each.

Substituting the existing clean-C guarded copy draft makes all three functions C. The normal whole-member oracle reports:

- Production 2.7.2: 104/108 raw words agree; the whole member is a mismatch.
- Homebrew 2.8.1 no-split: 105/108 raw words agree; the whole member is a mismatch, including its symbolic relocations.

These word counts localize output, not source distance. The no-split alternative's three differing `.text` words are at section offsets `0x170`, `0x1a0`, `0x1a4`. It emits an early `jr ra` instead of the original jump to a shared return, and puts destination setup in the final return slot. The corresponding original local-jump relocation is absent. Neither candidate is promoted or complete.

Inspection of the actual alternative source, `gcc/config/mips/mips.c:5671`, confirms that `mips_can_use_return_insn()` permits the return pattern after reload for an unprofiled leaf with no live RA and no frame. This explains an available backend mechanism for the measured direct return; it does not prove that no other clean C source can reproduce the target.

One additional controlled source test removes only the empty `do/while(0)` boundary around header formation in the current `realloc3` C. Both 2.7.2 and no-split 2.8.1 then mismatch at 104/108 words. The alternative therefore does not automatically eliminate that source-shaping requirement in this measured source/context.

## Decision

Do not silently replace the global compiler: the closest measured arm would regress thirteen currently exact members and does not solve the copy helper. Keep Homebrew 2.8.1 as a concrete, measured candidate. Its compatible set and target-default distinction are established; its historical role and a safe migration are not.

Tracked-state and configuration hashes before/after each run match. Pre-existing dirty files, including `calloc3.c`, are preserved. The compiler trial does not create a new function-completion or full-project verification claim.
