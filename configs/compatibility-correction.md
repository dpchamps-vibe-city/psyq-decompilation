# Library configuration and split compatibility correction

## Problem and missed onboarding check

The working `ResetRCnt` leaf did not exercise the mixed-member preparation path.
`SetConf` did: its converted size-zero export shares `.text` with unnamed private
callees. spimdisasm 1.40.1's early call scan interpreted ET_REL JAL addends as
listing coordinates without the section's ELF file base. It inferred phantom
boundaries inside `SetConf`; later relocation processing corrected operands but
not those earlier partitions. m2c consequently encountered a missing branch
label rather than a difficult C matching problem.

The reference-header configuration also pointed at the DOS-uppercase INCLUDE
tree on a case-sensitive host, while headers include lowercase paths. Without
`-nostdinc`, SDK `sys/*` includes could instead resolve to host Linux headers.
Initially we checked tool execution/simple functions, not full SDK preprocessing
and a real mixed member through disassembly, production TU compilation,
whole-member verification and m2c.

## Corrections

- `toolchain.json` include directories and `sdk.headers`, and `project.json`
  reference headers, now select `library-input/converted/include`.
  All 61 headers equal the supplied `library-input/psyq/INCLUDE` contents after
  newline normalization; originals were not changed. `flags.cpp` now includes
  `-nostdinc`, preventing accidental host-header substitution.
- Compiler version, optimization flags and per-member assembler profiles are
  unchanged. This is not a new historical compiler identification.
- The installed harness discovers private entries conservatively from original
  section-relative JAL relocations, rejecting sized interiors, fallthrough and
  cross-boundary shared blocks. Extents remain explicitly inferred.
- Original listing coordinates/bounds are passed before disassembler inference;
  emitted original code words and boundaries are validated before publishing.
  No installed Python package or original object is patched.
- Splitting preflights the batch and extends only exclusive canonical original
  assembly backlog. Already-matched callers retain established local helper
  names. Case-distinct original function filenames retain symbol-table ordinals.
  Existing C, shared headers and data files are preserved byte-for-byte.
- Original-word recognition classifies the six internal BIOS veneers as
  assembly-only backlog, not ordinary C tasks or new assembly-policy exceptions.

`libapi_73::SetConf` now owns `.text` offsets `0..0x220`
(544 bytes), followed by eight private entries: six 28-byte BIOS veneers and two
52-byte normal helpers. Complete `.text` remains `0x330` bytes. Helper names are
local listing spellings, **not runtime addresses**; member/section/offset are
still authoritative. Shared data remains separately represented.

## Reproducible end-to-end checks

```sh
npm run split-all
npm run library -- check-splits
npm run library -- preflight 'libapi_73::SetConf'
npm run library -- preflight 'libapi_72::ResetRCnt'
npm run check-all
```

- `check-splits`: **2,224/2,224 original reference-scaffold members match**,
  including all code/data bytes, symbols and relocations. This is explicitly
  not live-C acceptance and publishes no acceptance records.
- `check-all`: **all 2,224 configured live member TUs are byte-exact** under the
  unchanged whole-member oracle. Original assembly backlog is not decompiled C.
- Both real-function preflights pass SDK preprocessing, ordered TU validation,
  actual whole-member identity and fresh m2c generation. All configured reference
  headers preprocess successfully (1,744 witnessed SDK prototypes).
- `SetConf` generation no longer fails on the broken assembly boundary. Its
  raw C draft still contains unknown callee/pointer types and does not compile;
  completing its C preparation/matching is a separate task. A fresh `ResetRCnt`
  m2c alternative compiles but is not byte-exact; its existing live C remains
  unchanged and is certified by the whole-member check.
- 530 private entries were added across 137 manifests. Existing non-manifest
  source files and all selected original input hashes are unchanged.

Reports and reproducible command logs are under
`build/compatibility-investigation/` and `build/libraryPreflight/`.

The installed harness's `tools/agent/libraryPreflight.test.ts` exercises actual
production compilation/assembly, a size-zero export, unnamed private helper,
seven-word BIOS veneer, neighboring storage, strict whole-member comparison,
fresh m2c, and preservation of an already-matched caller's local helper names.
Negative controls reject DOS header casing, missing manifest functions and
wrong neighboring data. Additional tests cover conservative entry discovery,
listing completeness/literals, migration safety and stable filenames.

The broad harness suite has ten existing failures, also reproduced in a clean
HEAD archive with the same tools; that archive has one additional Git-metadata
check failure caused by its packaging. The new focused regression tests pass.
These unrelated baseline failures are not represented as a green full suite.

The target remains the 2,224 supported converted members; the six deferred
original conversions in `configs/deferred-sdk-objects.json` remain deferred.
These checks establish identity to the selected converted ELF objects, not
independent original-LNK encoding identity or complete clean-C reconstruction.
