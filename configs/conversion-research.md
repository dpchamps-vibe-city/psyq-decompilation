# Converter investigation

This was the source-only investigation. The subsequent user-authorized fetch,
build and 2,230-entry census are recorded in `configs/converter-exploration.md`
and `configs/converter-exploration.json`; they supersede the untested hypotheses
and next-step plan below. Neither target configuration nor input bytes changed.

## New user-provided provenance

The user identifies `../psyq2elf/` and
`../btn-decompilation/tools/vendor/psyq47/` as the converter/source trees, and
is nearly positive the older SYS headers shipped with 4.7 unchanged.
This is a user assertion about distribution provenance, not historical
compiler identification.

Read-only comparison confirms:

- All 2,231 files currently under `library-input/converted/` are byte-identical
  to corresponding files under the designated SDK tree's `converted/` directory.
- All 61 supplied headers are byte-identical to the designated tree's original
  `INCLUDE/` files after lowercasing paths. The five 4.6-labelled SYS headers
  already exist in that source tree. They were not changed by conversion.
- Original `LIB/` and `INCLUDE/` identities (94 files) and comparison results are
  retained in `configs/identification-origin.json`. No outside-project asset was
  imported or configured as a target.
- `../psyq2elf/` is the Jype project at
  `cba9b60d2f349a55e49530a28e01a10cae8771f1`, with a clean working tree.
  Its README documents testing with SDK 4.6. Its ELF writer sets OSABI NONE,
  and does not create the Redux conversion notes/log messages seen here.
- The supplied converted files/log identify PCSX-Redux `psyq-obj-parser`, so
  possession/use of the Jype checkout does not identify the implementation that
  produced this particular converted set. The exact Redux binary/revision/options
  used remain unknown.

## Candidate recommendation

For a matching-decompilation project, evaluate a pinned current PCSX-Redux
`psyq-obj-parser`, including its **`-c` COMMON-preservation option**. Do not
blindly replace existing targets or mix outputs from unrelated converters.
COMMON handling affects linker-visible storage and allocation; it is not merely
an output-format cosmetic choice.

The option was added by merged PR 1907:
https://github.com/grumpycoders/pcsx-redux/pull/1907
Merge commit: `2f2911345123a066f98abb98c65f4458c99e81f8`.
The current CLI says COMMON is converted into BSS by default; `-c` enables
ELF COMMON. This is a reason to evaluate it for faithful reconstruction, not
proof that the existing files must be discarded or that every LNK convention
is preserved.

Source reviewed from upstream commit
`78e777e160d840c37b17872d864a8d896681d191`:
https://github.com/grumpycoders/pcsx-redux/blob/78e777e160d840c37b17872d864a8d896681d191/tools/psyq-obj-parser/psyq-obj-parser.cc
Public source snapshot and its SHA-256 receipt are under
`build/identification/converter-research/`. This inspection did not build or
execute either converter.

## Why the five failures are special

Expression opcode 12 is `SECTION_START`, not an unidentified MIPS relocation.
The four standalone failures are startup objects needing linker-wide section
start/end semantics. The Jype converter explicitly translates section
start/end/size expressions into external symbols such as `__sbss_start__`,
`__bss_end__`, and `__text_size__`; that needs an appropriate linker-script
contract and is not a transparent format-only conversion.

Current Redux source has a `SECTION_START` branch, but that alone does not prove
correct conversion of these objects or support for their section-end/size
expressions. No successful retry is claimed. Its documentation explicitly
warns about CRT0 conversion:
https://github.com/grumpycoders/pcsx-redux/tree/main/tools/psyq-obj-parser

`libsn/snmain.obj` is also startup-related: its logged exports include `__main`,
and its relocations reference section boundaries, `main`, constructors and
destructors. The log records four initialized bytes in `.sbss`, not merely an
unallocated extent. The current Redux source still explicitly rejects data
inside BSS-named sections. Changing the name/type or dropping those bytes just
to get a successful conversion would require a semantic/layout proof.

## Bounded next step

Pin and compile the selected public converter only when authorized, then test
representative normal members and all five failed originals into a separate
`build/` output tree. Record executable hash/options and original-to-member
mapping; audit sections, symbol binding/COMMON, addends and HI16/LO16 pairing.
Keep startup failures explicit if unsupported. Replacing targets, updating
selection, or importing originals is a separate reviewed operation.
