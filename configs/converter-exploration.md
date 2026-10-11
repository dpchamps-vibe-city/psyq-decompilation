# Measured converter exploration

## Installed tooling

At the user's request, fetched a sparse public PCSX-Redux checkout into
`tools/pcsx-redux/`, pinned at `78e777e160d840c37b17872d864a8d896681d191`.
Initialized only the pinned ELFIO, fmt and magic_enum dependencies. Built the
unmodified parser with host g++ 13.3.0 and zlib, not the emulator.

- Builder: `tools/build-psyq-obj-parser.sh`.
- Executable wrapper: `tools/psyq-obj-parser`.
- Build outputs: `build/converters/pcsx-redux/<commit>/`.
- Reproducible exploration: `tools/explore-psyq-converters.mjs`.
- Instructions: `tools/README.psyq-converters.md`.
- Repository pins, executable/source hashes, command lines and summary:
  `configs/converter-exploration.json`.

For comparison, also compiled the user's existing clean Jype checkout at
`cba9b60d2f349a55e49530a28e01a10cae8771f1` directly into
`build/converters/jype-cba9b60/`. No source changes were made in either checkout.
No converter was added to `toolchain.json`; no target selection or flags changed.

## Coverage and extraction

Read all 23 original libraries (LIB v1/v2) and eight standalone LNK objects from
the explicitly user-designated source tree. The installed harness's existing
strict readers recovered **2,230 original entries**: 2,222 library members plus
eight standalone objects. Every extracted input is mapped by archive hash,
ordinal, source offset and member hash, never merely by basename.

Ran three experiments on every entry (6,690 conversions): Redux defaults,
Redux with `-c`, and Jype. Individual argv, status, output hashes, logs, ELF
summary and comparisons are in
`build/converters/exploration/all/report.json`. Input provenance/mapping is in
that directory's `inputs.json`. An earlier eleven-member focused run is retained
under `build/converters/exploration/focused/`.

## Full census

| Converter/mode | Emitted supported ELF | Failed |
|---|---:|---:|
| Redux, default | 2,224 | 6 |
| Redux, `-c` | 2,224 | 6 |
| Jype | 2,224 | 6 |

The successes all parse through the harness's supported ELF object adapter.
This is **format acceptance**, not proof of original-LNK fidelity or reconstructed
C. Failed processes/partial files are never counted as successful conversion.

### Redux failures

- `2MBYTE.OBJ`, `8MBYTE.OBJ`, `NOHEAP.OBJ`, `NONE3.OBJ`:
  `Unsupported relocation expression type: 22` (`SECTION_END`). The parser now
  gets past the old section-start failure but still lacks the needed complete
  section-boundary expression contract.
- `Libsn.lib[5] SNMAIN.OBJ`: `.sbss` looks like BSS but has data.
- `Libsn.lib[9] CACHE.OBJ`: `Unknown expression type 54`.
  The first failing HI16 relocation at `.text+0x10` structurally combines
  `0xA0000000` with an ADD expression (`.text` base plus `0x20`). Redux's
  expression parser has no case for opcode 54; its arithmetic meaning has not
  been independently established here.

Both default and `-c` have the same six failures.

### Jype failures

Assertions reject these original entries:

- `Libsn.lib[11] snctors.obj`, `[12] read.obj`, `[13] write.obj`: the first
  unsupported record is opcode 60 (`END_SLD`, source/debug information).
  They also carry function debug records 74/76; Jype has no handlers for those.
- `Libsn.lib[48] new_handler.obj`, `[56] eh.obj`: relocation kind 100
  (`GPREL16`, global-pointer-relative small-data addressing). Jype only accepts
  relocation kinds 16, 74, 82 and 84, so asserts on this valid additional kind.
- Standalone `MCGUI.OBJ`: section-base subtraction involving `0x10` at the
  HI16 relocation offset `0x100c` (and its LO16 at `0x1010`). Jype's normalized
  section-base branch requires ADD with a literal, not this SUB expression.

Jype emits ELF for **all five failures from the old conversion log**, including
SNMAIN. That makes it useful for investigation, but not a universally better
converter: it fails other real inputs and produces different ELF conventions.

A concrete fidelity warning was also found in Jype's **successful CACHE output**:
its expression reduction discards the outer opcode-54 operation and its
`0xA0000000` operand, keeping only the inner `.text` base plus `0x20`.
The emitted HI16/LO16 relocations target a local `.text+0x20` symbol. This is
not an implementation of the enclosing expression's arithmetic. Do not count
that success as a faithful conversion without independently establishing its
semantics and correcting the translation if necessary.

Parse-only verbose dumps for these cases are under
`build/converters/failure-causes/`, together with `cache-expression.json` and
`cache-jype.readelf.txt`. No parser source or target bytes were modified.

## COMMON experiment

Comparing Redux default to `-c` with the normal symbolic object oracle gives:

- 2,188/2,224 pairs equivalent under the oracle.
- **36 objects differ**, exposing **162 ELF COMMON symbols** with `-c` instead of
  locally allocated BSS symbols.
- Examples include GPU `_que`, SDK heap variables, pad state and callbacks.

Full delta: `build/converters/exploration/common-effect.json`.
COMMON preservation is materially relevant to faithful linking. It is not a
cosmetic flag and must not be introduced into an existing converted target set
without reviewing provenance/layout and retesting target identity.

## Completeness defects in the old converted set

### Duplicate names in LIBGTE

The original `LIBGTE.LIB` has 539 indexed members but the old converted archive
contains only one per extracted basename. Eleven name groups repeat, with
**30 extra entries**. Every repeated group has distinct LNK hashes:

- `SMP_00_1.OBJ`, `CLIP_FT_.OBJ`, `CLIP_GT_.OBJ`: three versions each.
- Eight `PRS_*` name groups: four versions each.

Ordinal staging preserves them all. The old basename-based copies cannot
represent every variant. A comparison with an old named copy is explicitly
marked `ambiguousNamedBaseline`; it does not establish which original variant
that copy came from. Do not reuse the old extracted-name/archive-building
workflow for an authoritative full-library reconstruction.

### LIBSN v2 coverage

The designated original `Libsn.lib` has **59 indexed members**, but the old
converted set contains only nine named objects. Fifty original entries have no
baseline: SNMAIN (a known logged failure) and **49 additional entries**.
Redux converts 48 of those 50; Jype converts 45. The reason they were missing
from the old conversion is unresolved; the previous log's five errors do not
explain the full coverage gap.

## Diagnostic baseline comparison

The normal symbolic ELF object comparator, without relocation masking, was used
against the old named `.o` copies:

- Redux default/`-c`: 1,238 matches among 2,176 named comparisons each.
  Excluding ambiguous duplicate-name mappings: 1,229/2,135 each.
- Jype: 0 matches among 2,175 named comparisons (2,134 unambiguous).

Mismatch is not proof that an older conversion is correct. Changes involve
encoded relocation addends/order, symbol binding/allocation, section layout and
ABI flags. Jype sets `0x1001` versus the baseline's `0x1000` and emits additional
empty sections; those alone prevent whole-object equivalence. Raw file hashes
also include source-path/note/debug metadata, so raw-file mismatch is not the
iteration/fidelity metric.

The different defaults must not be mixed into a target set just to make all
input filenames appear. A fresh converted set would be a new, separately
reviewed target/provenance selection, not an automatic repair of current targets.

## SNMAIN boundary case

A parse-only verbose dump confirms its `.sbss` payload is **four zero bytes**.
Redux rejects initialized payload records in BSS-named sections even when the
bytes happen to be zero. Jype emits a four-byte SHT_NOBITS `.sbss`, and emits
external section-start/end/size symbols requiring a linker-script contract.
Successful emission does not prove the startup/constructor/boundary semantics.

Evidence:
`build/converters/snmain-original.dump.txt`,
`build/converters/snmain-jype.readelf.txt`,
`build/converters/2mbyte-jype.readelf.txt`.

## Result and next bounded work

Neither converter is an unconditional replacement. Current Redux with `-c` is
a useful base for preserving COMMON, but still needs explicit startup and CACHE
expression support for full coverage. Jype is a useful independent witness for
the five old failures, not a proven canonical oracle.

Before replacing targets: audit original-to-ELF relocation semantics, decide
COMMON policy, preserve duplicate member identities and include the entire LIBSN
index. Targeted conversion-adapter work should start with the six named Redux
failures and explicit section-boundary symbols, not a wholesale switch based
only on conversion-success counts.

Rehashed all 2,231 existing supplied files and all 94 recorded source-tree files:
**unchanged**. No reconstruction, target overwrite, system package installation,
compiler/flag authority change, or commit occurred.
