# Toolchain identification — evidence and configured decisions

## Configured assembler adoption (2026-10-13)

The initial-pass sections below are historical, not the current target or
compiler configuration. `project.json` now selects the 2,224 ordinal-preserving
Redux/COMMON objects under `library-input/redux`; the compiler candidate remains
GCC 2.7.2, with compiler and assembler `-G0`.

> **Update 2026-10-17.** The compiler identification below is superseded. The
> library objects were produced by a GCC development-trunk snapshot dated
> between 1997-02-05 and 1997-03-18, run in MIPS-assembler output mode; the
> production compiler is now `tools/gcc-recipes/trunk-19970318-psx/` with
> `-mmips-as -fno-exceptions`, and both per-TU flag overrides are retired. See
> `notes/research/compiler-identification-1997-trunk.md` (evidence) and
> `notes/research/compiler-identification-methodology.md` (method). The
> assembler findings below stand.

The configurable-backend harness is adopted in `toolchain.json`:
- Base: direct GNU as, `inputRewrites: ["move-addu", "rdata-section"]`, default optimization.
  The read-only-data rewrite preserves the `.rdata` name witnessed in 154
  originals (40 with switch tables), rather than ELF GAS's `.rodata` alias;
  see `plans/harness-rdata-section-rewrite.md`. It changes assembler input,
  not the strict whole-member oracle.
- `sn-aspsx`: MASPSX, retaining the former unpadded profile and its 38 libsn
  selections. MASPSX's public pin and ASPSX 2.80 candidate mode are unchanged.
- `sn-aspsx-padded`: MASPSX with base padded assembler flags, assigned to the
  remaining 16 converted members with independently witnessed native packaging.
  Keeping a separate padded profile avoids borrowing the unpadded-section rule.

Fresh harness identification reproduces the original-word census:
**455 indexed integer loads with destination != index use the destination as
scratch (GAS rule), zero use $at (ASPSX rule), and 160 destination == index sites
use $at (ambiguous between both)**. The 455 discriminating sites span 133
members and 19 libraries. Absolute destination-reusing loads are expected under
both assemblers, not a compiler address-splitting fingerprint.

The native LIB/LNK record census reports **2,167 GNU-converter-style objects**
(section IDs in the 0xF000 family, no file records or constructors), **48
ASPSX-native-style objects**, **14 ambiguous objects**, and **one incomplete
object**. The four converter-style members whose first section is 0xF004 also
use 0xF000 for .text; a first-section-only 0xF001 test would miss them. The
incomplete libsn CACHE object contains unsupported expression opcode 54;
absence of later records is not asserted and its semantics were not guessed.

All 48 native-style libsn objects are present in the converted selection.
Thirty-two already had the unpadded profile; sixteen now receive the padded
MASPSX profile. Six additional original unpadded selections (ordinals 2, 4, 6,
7, 8 and 10) are retained for compatibility, **not newly identified as native
ASPSX builds**. The remaining three converted libsn members have ambiguous
packaging and inherit base; no further historical-family claim is made.

This SDK-wide GNU-built Sony-library conclusion combines independent indexed
load rules, converter-style packaging and actual same-input assembler tests;
release-tool distribution metadata alone did not establish it. Real ASPSX 2.86
and MASPSX agree on the former StopRCnt residual, so MASPSX is not defective.
The macro delay-slot census (590 swap sites, including 210 $at sites) and
SetInitPadFlag's three-word leaf require GAS's default reorder optimization,
not `-O1`. Compiler-version identification remains outside this change.

All **123** previously accepted members were re-verified as whole-member
MATCHes. StopRCnt (**92/92**) and SetInitPadFlag (**164/164**) were separately
integrated and passed the official full member, scope, source-policy and context
publication gates. Both members already belonged to the accepted set through
matched neighbors. No warnings occurred in 125 retained GAS production
receipts; both new expansion listings reproduce their production objects
byte-for-byte. This does not verify or reconstruct the 2,101 backlog members.

Evidence: `build/assembler-backend-evidence/configured-identification.json`,
`reverification.log`, the two `*.finalization.json` reports,
`expansion-captures.jsonlog`, and `assembler-warnings.json`.
See `notes/stoprcnt-investigation.md` §19 and
`plans/configurable-assembler-backend.md`. Generated project-profile wording now
reports the actual assembler per profile rather than asserting universal ASPSX
semantics. Target-specific conclusions stay in this project, not harness docs.

## Historical initial evidence pass

## Scope and configured decisions

The user chose PCSX-Redux for subsequent PSY-Q 4.7 conversion and deferred the
six unsupported originals, without excluding them from eventual full-SDK scope.
`toolchain.json.tools.psyq2elf` now selects `tools/psyq2elf-redux`. This executable
adapter accepts the harness's two-positional-argument ABI (`INPUT.OBJ OUTPUT.o`)
and invokes the pinned upstream parser as `INPUT.OBJ -c -o OUTPUT.o`.
The COMMON-preserving policy, source pin, wrapper/executable hashes and backlog
reference are in `configs/conversion-policy.json`.

This is a **converter choice**, not historical compiler identification.
`project.json` still selects the old converted archives; no target was replaced.
A fresh ordinal-preserving target-set migration is a separate reviewed step.
Do not run image-only SDK integration to perform library-target migration.

## Measured distribution evidence

The user-designated `Psy-Q_47.zip` has SHA-256
`e3df241adde663fba1f5bff1f0070e0d32d9518ebb11d60a914e5e016f704745`.
It contains 101 entries. All 94 recorded source files under its LIB/INCLUDE
roles match the designated loose originals byte-for-byte.

The included `LIB/readme.txt` (also present under INCLUDE) explicitly identifies
"Run-time Library Release 4.7", February 2000. Its SDevTC tools change list says:

- `aspsx.exe`, `cc1psx.exe`, `cc1plpsx.exe`, and `cpppsx.exe` were updated.
- `pssn/gnusrc/gcc295s.zip` (GCC 2.95 source) was added.
- `pssn/gnusrc/gcc281s.zip` (GCC 2.8.1 source) was removed.

This is actual supplied release-document evidence for the **GCC 2.95 family**
being distributed with 4.7. It does not identify the exact point release or
prove that every prebuilt library member was recompiled with it.
The five SYS headers carrying 4.6 markers match the supplied packaged originals;
they are consistent with carried-over headers, not evidence of conversion mixing.

The archive does **not** contain the mentioned PSSN tool executables or GCC source
ZIPs, so their historical versions cannot be read directly from this input set.
No proprietary tool binaries or SDK files were downloaded or imported.

Reports:
`build/identification/toolchain/sdk-zip-inventory.json`,
`build/identification/toolchain/sdk-package-comparison.json`.

## Original-object source provenance

Scanned the 2,230 original entries already staged during converter exploration.
Forty-five LIBSN entries have parser-confirmed FILENAME records naming the source
path `D:\SOURCE\GCC\gcc-2.8.0\LIBGCC2.C` (or the corresponding runtime source).
These include integer helpers, exception/runtime support and `new_handler`.
All 45 version-bearing witnesses were independently replayed with Redux's
parse-only verbose mode; no conversion or source reconstruction was needed.

**Interpretation:** LIBSN contains GCC 2.8.0-source-provenance runtime code.
A filename identifies a source tree, not the compiler executable that built it;
GCC 2.95 could compile retained GCC 2.8.0 runtime sources. Older compiler builds
or mixed prebuilt-library history remain competing hypotheses. Do not force a
single historical compiler version onto all SDK members based on this pathname.

The complete scan found 48 source-record-shaped candidates, all `.c` spellings;
that is not a census proving all other entries were handwritten assembly.

Reports:
`build/identification/toolchain/original-metadata.json`,
`build/identification/toolchain/gcc-source-records.json`,
`build/identification/toolchain/source-records/`.

## ABI, assembler and flags

- Supported converted targets are ELF32 little-endian MIPS ET_REL. ELF flags and
  Linux OSABI notes belong to conversion; they are not original compiler labels.
- Original LIBSN has GPREL16 relocations (e.g. `new_handler`, `eh`) and small-data
  sections. This witnesses GP-relative addressing but does not uniquely identify
  the configured `-G8` threshold.
- The release notes name ASPSX but do not give its version. ASPSX 2.80 emulation
  remains a supported **candidate**, not a detected assembler release.
- Existing `-O2`, char signedness, struct-return, small-data and other flag choices
  remain bootstrap candidates. No per-TU override was created and no flags were
  chosen solely to improve a matching score.
- SDK file-format/overview PDFs were extracted to build-local text for searches;
  they did not supply a compiler point release or a LNK opcode-54 definition.
  They are not permission to guess that operator's arithmetic.

## Local capability check

The converter binary is present and its configured adapter successfully converts
a real GPU member. The result has `_que` in ELF COMMON, demonstrating the wrapper
actually applies `-c`; this is a converter-protocol/policy check, not a C match.

Cross-cpp/binutils, Python and pinned maspsx/m2c support are available. Docker
server access succeeds (29.7.2). Subsequently provisioned the supported public
GCC 2.95.2 candidate through the harness's Docker/BuildKit recipe, at
`build/dependencies/compiler/gcc-2.95.2-psx/cc1`.
The executable reports GNU C 2.95.2 19991024 (release), target `mips-sony-psx`.
Its SHA-256 is `2aa85925dfa10855107c78e29ec36965b953976a45b1a47fb68beb5a74096079`;
recipe identity is `df58477447cbd4982c256783a0dd561b12bfec22309dc3dbfaa951de0f45d861`.
Build/probe evidence: `build/identification/toolchain/compiler-provision.log`,
`cc1-version.stderr`, and the compiler cache's `compiler-provenance.json`.
The recipe's capability smoke checks pass; this establishes an available
candidate, not historical compiler identity. A subsequent build-only real-member
probe is described below; its strict whole-member result is MISMATCH.

The pinned public old-gcc source recipes include PSX candidates 2.8.0, 2.8.1,
2.95.1 and 2.95.2. Recipe availability is not historical identification.
The harness provisions its supported 2.95.2 candidate on demand: reading
`configuredTool("cc1")` triggers that build when absent. This was used explicitly
after the source/release evidence pass, not mistaken for a detection result.
Forensic adapters are currently tied to the retained GCC 2.95.2 source/semantics;
changing the compiler path/version alone does not implement mixed-version or
GCC-2.8-specific allocation/scheduler analysis.

## First real-member pipeline probe

Authored one **build-only** C hypothesis for `SpuGetTransferStartAddr`, using the
supplied SDK `unsigned long(void)` signature and views matching its original
LHU/LW accesses. Pre-author triage/frame mapping ran; post-author triage had no
findings and callee truth found no direct calls. The probe is valid for the
ordinary shift-count domain 0..31, not a claim about the canonical global types
or arbitrary invalid SDK state. No `src/` file was created.

The higher-level fuzz wrapper required an existing owning source TU and refused
this unstarted target. The normal library backend accepts a complete alternate
source, so it was used instead: `measureLibraryFunction` compiled the whole
member and ran the unchanged strict symbolic object oracle.

**Result:** all six executable instruction words and their relocations agree.
The target contains two additional zero padding words, and whole-member identity
fails on ELF representation:

- Flags: converted target `0x1000`, compiler/GAS candidate `0x1001`.
- `.text`: target size/alignment 32/8, candidate 24/16.
- Candidate also has empty allocated `.data`/`.bss`, plus allocated `.reginfo`
  and `.MIPS.abiflags`; the converted target has only `.text`.

The same strict mismatch was replayed against fresh selected Redux/`-c` output
for original `LIBSPU.LIB[52] s_gtsa.obj`, not just the older named baseline.
Original LIB ordinal 52 is **not** its old converted archive ordinal 27.
The six-word agreement is evidence that this candidate emits this leaf's code,
not that GCC 2.95.2 uniquely identifies every library's historical compiler.

These differences require a reviewed **LNK/ELF versus compiler/GAS representation
contract** before deeper source/flag searches. Do not hide them by masking ABI
flags, dropping allocated sections from the oracle, or choosing flags merely to
improve the score. Preserve target bytes until any proposed conversion/assembler
normalization has independent semantic justification and explicit approval.

Reports/source:
`build/identification/toolchain/SpuGetTransferStartAddr.c`,
`real-member-probe.json`, `real-member-probe.log`,
`redux-real-member-probe.json`, and their retained production compiler artifacts.
No member is recorded as verified.

## Next measured task

1. Resolve the ELF representation discrepancies above while retaining strict
   verification; establish an explicit converter/assembler contract.
2. Prepare a reviewed Redux/COMMON target set with archive ordinals preserved,
   2,224 convertible entries and the six explicitly deferred originals retained
   in the separate full-SDK ledger. Keep old conversions immutable.
3. Use the now-provisioned supported GCC 2.95.2 candidate for measurements, with
   its binary/source/build hashes retained. If original PSSN version-bearing
   binaries or source archives are available locally, inspect them before
   narrowing the historical point release.
4. Compare additional representative **real original members** from ordinary C libraries
   and LIBSN runtime code through the normal symbolic whole-member oracle.
   Distinguish compiler/assembler/ABI/conversion differences; success on a tiny
   smoke test cannot identify a compiler version.
5. Test older GCC candidates only when a real-target residual or independent
   provenance points at them. Keep unresolved/mixed-version requirements explicit
   rather than silently assigning GCC 2.95.2 to the complete SDK.

Only the one build-local C probe was authored; no source TU was integrated,
target split/matching campaign started, whole-member identity established, or
commit made by this pass.
