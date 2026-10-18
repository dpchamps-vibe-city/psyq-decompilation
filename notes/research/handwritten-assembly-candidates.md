# High-confidence assembly candidates: whole functions or mixed C/assembly?

## Scope and conclusion

This note records the original-code investigation behind the handwritten-assembly
scanner's twelve high-confidence candidates. It is **research, not a completed
matching-decompilation report**. These functions have not been converted to `.s`
by this work, and no fresh function or whole-object byte-match claim is made.

**Current interpretation: all twelve are likely whole-function assembly, rather
than ordinary compiled C functions containing one small assembly operation.**
`setjmp` and `longjmp` are the strongest cases. The other ten have manually
managed call/return machinery, in addition to their BIOS or code-patching roles.

This is an inference about implementation style, not recovered historical
source. The original words do not distinguish a standalone `.s` implementation
from a C file containing assembly that emits essentially the entire routine.
Nor does this investigation prove that no clean-C or evidence-backed macro
reconstruction could match a particular function.

The current individual `.c` files are reconstruction fragments/placeholders.
Their extensions do **not** establish that the original implementations were C.

## Current candidate list

Scanner version 4, default nomination threshold **80/100**:

| Function | Score | Selected original object / current TU directory |
| --- | ---: | --- |
| `_patch_pad` | 98 | libapi / 74-patch |
| `_remove_ChgclrPAD` | 98 | libapi / 83-chclrpad |
| `_InitGun` | 95 | libgun / 1-newgun |
| `_patch_gte` | 95 | libgte / 226-patchgte |
| `_patch_card` | 95 | libcard / 14-patch |
| `_patch_card_info` | 95 | libcard / 14-patch |
| `_patch_card2` | 95 | libcard / 14-patch |
| `_mcxStartFastDsr` | 95 | libmcx / 30-mcxdsr |
| `_padGunInitHook` | 95 | libpad / 20-pdhokres |
| `setjmp` | 90 | libc2 / 39-setjmp |
| `_mcxStopFastDsr` | 85 | libmcx / 30-mcxdsr |
| `longjmp` | 85 | libc2 / 39-setjmp |

Scores are **heuristic support, not probabilities**, historical-source proofs,
or source-policy exemptions. A score of 95 does not mean 95% of the function
was assembly, or a calibrated 95% probability of assembly origin.

The current full census contains 3,201 functions: 12 high, 4 medium, 3,131 low,
and 54 undetermined. All 136 existing C definitions are protected; none currently
scores high. That observation is a useful check, not a measured false-positive
rate for the unresolved backlog.

## What the distinction means

There are three separate questions:

1. **Function implementation:** did a compiler generate an ordinary C function
   around a small assembly operation, or does the whole routine have a manually
   controlled assembly skeleton?
2. **Code layout:** does a symbol's inferred extent include executable code,
   copied instruction templates, saved runtime words, or padding?
3. **Historical source/module composition:** was the containing object built
   from assembly alone, C alone, or some combination?

The twelve candidates provide strong evidence for the second alternative in
question 1. Several also have complicated layouts under question 2. Neither
observation alone settles question 3 for every neighboring symbol.

A loop or pointer expression being expressible in C does not establish that it
was originally C. Conversely, a C function copying assembly bytes is still
potentially a C function. The scanner therefore requires independent structural
evidence; copied code alone cannot nominate a function.

### The common whole-function evidence

Ten candidates save the incoming `$ra` in non-stack storage, make linking calls,
reload `$ra` from that same storage, and return without a reachable `$sp` write.
The schematic shape is:

```asm
lui   $at, %hi(saved_ra)
sw    $ra, %lo(saved_ra)($at)
# Linking calls and the routine's work, without allocating a normal call frame.
lui   $ra, %hi(saved_ra)
lw    $ra, %lo(saved_ra)($ra)
nop
jr    $ra
nop
```

Here `saved_ra` is an explanatory name, not a recovered original symbol.

This is not merely a privileged instruction inside an otherwise ordinary C
function: the unusual part includes the routine's entry, call preservation and
exit. A normal compiled non-leaf C function would ordinarily preserve its return
state using its call frame. Assembly macros could hide calls from a compiler,
so the shape remains evidence rather than an impossibility proof.

`setjmp` and `longjmp` instead qualify through explicit architectural register
context save/restore, including `$sp` and `$ra`.

## Per-function findings

### `_patch_pad` — likely whole-function assembly

- Saves the incoming `$ra` globally and restores it after linking calls, with no
  stack allocation.
- Calls `EnterCriticalSection`, performs a BIOS B0 transfer with selector `0x57`,
  and obtains a driver pointer through the returned table.
- Forms two driver-relative addresses using trapping `addi` encodings and
  publishes them for the neighboring PAD entry points.
- Clears eleven words in the runtime driver and calls `FlushCache`.

The loop and stores could be described in C, but the call skeleton and instruction
choices support a hand-authored routine throughout, not one isolated asm island.

### `_remove_ChgclrPAD` — likely whole-function assembly

- Uses the same global-return-state/no-frame pattern.
- Performs a BIOS B0/`0x57` transfer and computes a driver-relative patch address
  with trapping `addi`.
- Clears nine words, calls `FlushCache` and `ExitCriticalSection`, then restores
  the saved return address.

Again, the evidence covers the routine's calling machinery as well as its patch
operation. The score is not based on the underscore or patch-related name.

### `_InitGun` — likely assembly installer with an associated assembly handler

- Has the global `$ra` preservation pattern and BIOS B0/`0x56` transfer.
- Copies a **16-byte** `lui` / `addiu` / `jalr` / `nop` template from
  `_clear_gun_flag + 0xC`.
- The resolved target is `read_gun_h + 0x14`, an interior entry rather than the
  ordinary `read_gun_h` entry.
- The target-side trace reaches an interrupt-context restore and `jr $k0` with
  `rfe` in its delay slot.

The installer itself looks assembly-shaped. The copied template and handler are
additional assembly code, not evidence of a compiler-generated C portion.
The ordinary getters elsewhere in this object are a separate provenance question.

### `_patch_gte` — likely assembly installer plus embedded instruction templates

- Has the global `$ra` preservation pattern and BIOS B0/`0x56` transfer.
- Compares six runtime words against an embedded expected fragment before
  conditionally copying a six-word replacement.
- The replacement contains kernel-register-based context stores and COP0
  Cause/EPC reads. These are exception-context instructions, not merely a GTE
  command macro in an ordinary C algorithm.
- Calls `FlushCache` and `ExitCriticalSection`, then restores its saved `$ra`.

The symbol extent includes the installer, expected/replacement code templates,
and padding. **Code plus copied-code templates is not the same classification
as C plus inline assembly.** Template instructions are not counted as direct
execution from the installer's entry.

### `_patch_card_info` — likely assembly routine plus appended payloads/templates

- Its normal entry saves `$ra` globally, performs a BIOS B0/`0x57` transfer,
  computes a driver-relative address using trapping `addi`, patches a word,
  calls `FlushCache`, and restores `$ra`.
- Only 17 of the 55 words in its inferred extent are reachable from that entry.
- The remaining extent includes independently referenced patch code and two
  transfer templates, not just a continuation of the exported routine.

The current section-relative layout is:

| Range | Observed role |
| --- | --- |
| `.text + 0x00 .. 0x44` | Normal-entry `_patch_card_info` routine |
| `.text + 0x44 .. 0xB4` | 112-byte payload copied into RAM by `_copy_memcard_patch` |
| `.text + 0xB4 .. 0xC8` | 20-byte transfer template used by `_patch_card` |
| `.text + 0xC8 .. 0xDC` | 20-byte transfer template used by `_patch_card2` |

These are recovered layout roles, not recovered original source labels. Inferred
symbol size has grouped multiple pieces of code under one current function name.

### `_patch_card` — likely whole-function assembly installer

- Uses global `$ra` preservation and BIOS B0/`0x56`.
- Reads two words from runtime code, extracts their low halves and reconstructs
  an address before selecting the patch destination.
- Copies the 20-byte template at `_patch_card_info + 0xB4`.
- That template jumps to `0xA000DFAC`.
- A companion bounded copy deploys the 112-byte source payload at physical RAM
  `0xDF80`; the template target is its uncached RAM alias plus `0x2C`.
- Calls `FlushCache` and returns through its saved global `$ra`.

The address/deployment relationship establishes intentional treatment of the
copied words as code. It does not by itself establish runtime call order or prove
that the entire payload has been semantically reconstructed.

### `_patch_card2` — likely whole-function assembly installer

- Uses the same global `$ra` calling skeleton and BIOS B0/`0x57`.
- Copies the 20-byte template at `_patch_card_info + 0xC8` into runtime driver
  code.
- That template calls through `0xA000DF80`, the uncached alias of the independently
  witnessed RAM deployment's start.
- Flushes the instruction cache and restores its saved return address.

Both card installers are likely assembly routines operating on other assembly
fragments. The existence of a simple companion copy helper does not prove the
whole containing object was one language.

### `_mcxStartFastDsr` — likely whole-function assembly setup routine

- Preserves `$ra` in shared global storage, without a normal call frame.
- Initializes shared state and lazily obtains/caches a BIOS-derived code pointer.
- Calls a same-object comparison helper, then conditionally saves **12 bytes**
  from that pointer into `_mcxVecSave`.
- Installs a **16-byte** local-call template from `_mcxVecDsr` through the same
  cached pointer and calls `FlushCache`.

The complete save/install/restore relationship is witnessed across the start and
stop routines. The installed template targets `_mcxFastDsrEnt`; handler
continuations cross the current inferred symbol boundaries. Those boundaries
must not be mistaken for historical assembly procedure boundaries.

### `_mcxStopFastDsr` — likely whole-function assembly teardown routine

- Uses the same shared global return-state slot and no call frame.
- Checks the cached pointer and same-object comparison helper.
- Restores the saved **12-byte prefix** from `_mcxVecSave` through the same
  pointer, calls `FlushCache`, and restores `$ra`.

The save/install/restore sizes are **12 / 16 / 12**, not 16 / 16 / 16. The
installed fourth word is a nop delay slot. The lifecycle is supporting evidence;
the stop routine's independent calling-convention shape is what makes this more
than an ordinary C memory-copy function.

### `_padGunInitHook` — likely assembly installer with an associated assembly handler

- Preserves `$ra` globally, saves its arguments to shared storage, performs
  linking calls without allocating a stack frame, and uses BIOS B0/`0x56`.
- Copies **12 bytes** from `_padClrHitCount + 0xC`: `lui`, `addiu`, and `jalr`.
- The resolved target is `_padClrHitCount + 0x2C`, an interior handler entry.
- That entry's trace reaches kernel-register context restoration and
  `jr $k0` / `rfe`.
- Calls `FlushCache`, reloads the original `$ra`, and returns.

**The fourth source word is nop, but it is not copied. The destination delay
slot is unknown from this copy.** The analysis must not describe this as a
four-word installation.

The ordinary `_padClrHitCount` entry merely clears a counter and returns; it is
C-compatible. Its inferred extent also contains the template and handler. That
layout does not establish that the ordinary entry was C, nor that its primary
entry executes the embedded handler.

### `setjmp` — very strong whole-function assembly interpretation

- Explicitly stores the caller's `$ra`, `$gp`, `$sp`, `$fp`, and `$s0`–`$s7`
  into a buffer addressed by `$a0`.
- Sets the return register and returns without a conventional call frame.

The operation depends on architectural register state that ordinary portable C
cannot directly name. A compiler intrinsic or assembly embedded in a C file is
an alternative source form, but this is an assembly-level implementation rather
than a C algorithm with one incidental asm instruction.

### `longjmp` — very strong whole-function assembly interpretation

- Explicitly reloads `$ra`, `$gp`, `$sp`, `$fp`, and `$s0`–`$s7` from the buffer.
- Moves the supplied value into the return register and jumps through the
  restored return address.

Restoring the stack and return context is the routine's central operation. The
observed implementation is assembly-level throughout; no ordinary compiled C
wrapper is visible around it.

## Whole objects versus individual candidates

The candidates occupy eight selected original objects. Their current TU manifests
retain that object ownership, but do not recover historical source filenames or
prove that an object was produced from only one source file.

| Object | Ownership/layout considerations |
| --- | --- |
| libapi / 74-patch | Also contains `EnablePAD` and `DisablePAD` loaded-pointer tail transfers. |
| libapi / 83-chclrpad | One discovered function plus storage/padding; no separate compiled-C region was identified. |
| libgun / 1-newgun | Contains installer/teardown, simple getters, transfer templates, an interrupt handler and additional code/storage. |
| libgte / 226-patchgte | One discovered routine with embedded expected/replacement instruction fragments. |
| libcard / 14-patch | Contains three assembly-shaped patch routines, a copy helper and embedded payloads/templates. |
| libmcx / 30-mcxdsr | Contains setup/teardown, comparison code, a call template, handler continuations and runtime-filled code storage. |
| libpad / 20-pdhokres | Contains installer/teardown, simple counter helpers and an interior interrupt handler. |
| libc2 / 39-setjmp | Contains the two explicit register-context routines. |

Some entire objects look plausibly assembly-authored. However, **a C-compatible
neighbor is not proof of historical C, and an assembly candidate does not prove
that every neighbor was assembly**. Do not convert whole mixed/undetermined
objects solely because one candidate exceeds the threshold.

Inspection of the eight converted ELFs' symbol tables found FILE entries naming
converter output paths, not recovered original `.c`/`.s` source filenames. That
inspection therefore did not settle historical source composition. Generated
spimdisasm `Handwritten function` comments were not used as independent evidence.

## Scanner interpretation and reconstruction recommendation

- Treat these as candidates for **complete assembly routine reconstruction**,
  preserving original object ownership and relocation/layout requirements.
- Keep ordinary C and justified shared operation macros available for functions
  whose actual evidence supports those representations. A BIOS operation or GTE
  instruction alone is not grounds to classify an entire function as assembly.
- Keep copied payloads, templates and runtime-filled storage explicitly distinct
  from normal-entry executable instructions.
- Assess neighboring helpers separately. The scanner does not grant permission
  to overwrite existing C or nominate an entire object by association.
- Do not use this note as a proof of compiler impossibility, a reason to change
  the configured compiler/flags, or an automatic assembly-emission authorization.

Scanner v4's code-patching observations share a combined **+20 cap**. A bounded
copied-transfer template must resolve to a traced same-owner entry or an
independently witnessed RAM deployment. Arbitrary instruction-shaped data, an
underscore name, a magic address, or a failed C attempt is not enough.

The rule moved `_patch_card`, `_patch_card2`, `_padGunInitHook`, and `_InitGun`
from 75 to 95. `_padGunExitHook` remains 75: its NOP teardown does not satisfy
that copied-transfer rule. A lower score does not establish C origin.

## Evidence, identities and reproduction

### Original-object identities

| Current directory | Member ID | Selected input SHA-256 |
| --- | --- | --- |
| libapi/74-patch | `libapi_74` | `88562458770e8b1986ea038b0699e1f614fcc9804808de4e3165f50acee731f1` |
| libapi/83-chclrpad | `libapi_83` | `135304800d81bd2b54837ce7b3c29d3baf2020d3bab189e90ac3e1540faf99df` |
| libgun/1-newgun | `libgun_1` | `0c26f12f2f7170c449398de9d7396dc195fc848bd35820fc0c6447944e012672` |
| libgte/226-patchgte | `libgte_226` | `c6130afb8d8d229c176b3ca6016a1c05d073fd1563caee1bc8ac9848a24a2bc3` |
| libcard/14-patch | `libcard_14` | `5af0e6f84af449368adcc182c3b1443305dcdc63099bcba1ca9950580edf097d` |
| libmcx/30-mcxdsr | `libmcx_30` | `58546b4ddd5464285d93bd97bfb5ad483f4ea68808ceefcde20d3fd895d7914e` |
| libpad/20-pdhokres | `libpad_20` | `5214f92856a20f7fc8c18784247c011f995615405c6202925dcb56d2ca603ec8` |
| libc2/39-setjmp | `libc2_39` | `599432f4f3a254d04a0af457a49ba5a265b443fb61625d61a933ba3e9fa3491f` |

Input paths are `library-input/redux/<directory>.o`; current ownership manifests
are `src/libraries/<directory>/tu.json`. Original-word disassemblies are under
`build/libraries/disassembly/<member-id>/member.s`.

These identities bind the conclusions to the selected converted inputs. They do
not independently verify native LIB/LNK conversion fidelity.

### Retained diagnostic artifacts

- `build/handwrittenAssembly/report-v3.json`: pre-template-rule census.
- `build/handwrittenAssembly/report-v4.json`: version-4 census.
- `build/handwrittenAssembly/report.json`: current report; mutable on later scans.
- `build/handwrittenAssembly/card-pad-v4.json` and `.txt`: requested card/PAD
  installers, sibling installer and PAD teardown evidence.
- `build/handwrittenAssembly/card-pad-companions-v4.json` and `.txt`: `_InitGun`
  and companion normal-entry classifications.

These `build/` artifacts are local/ignored. Reports retain original-word and
relocation hashes, selected toolchain context, instruction evidence, copied-byte
counts, resolved target coordinates and cross-function witnesses.

Reproduce the full scan from the project root:

```sh
node tools/harness-proxy.mjs tools/diagnostics/handwrittenAssembly.ts \
  --output build/handwrittenAssembly/report.json
```

Inspect an individual function with its same-owner witnesses:

```sh
node tools/harness-proxy.mjs tools/diagnostics/handwrittenAssembly.ts \
  --function _patch_card --function _padGunInitHook
```

The scanner records the configured compiler; it does not identify the historical
compiler or compile these candidates. The active project's configured compiler
is GCC 2.7.2; harness defaults are not evidence for substituting another version.

### Tooling validation, not reconstruction verification

The scanner's broader regression selection completed with **124 passed,
10 skipped, zero failed** tests. Tests cover synthetic original words, real ELF
relocation/address resolution, interior entries, RAM aliases, copied-prefix
lengths, negative counterfactuals and existing-C protection. The full project
census was replayed with identical report contents after the final tooling edit.

The harness-wide TypeScript check still reports inherited errors; the recorded
run had no diagnostics in the handwritten-scanner implementation/test files.
No clean whole-project typecheck, function MATCH, or whole-object reconstruction
verification is claimed by this note.
