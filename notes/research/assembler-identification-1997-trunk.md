# Which assembler built the PSY-Q 4.7 library objects: a 1997 GNU as trunk snapshot producing ECOFF

Date: 2026-10-17.

Scope:
- Identify the assembler behind the GNU-built library members.
- Replace the two harness text rewrites that stood in for it (`move-addu`, `rdata-section`).
- Record a reproducible artifact.

Method:
- Each candidate assembles the project's own assembler input. For C members that is the production cc1 (`trunk-19970318-psx`, production flags) output.
- The result is compared with the original. Section 4 explains why the comparison is against the original SDK objects rather than the converted ELF targets.

Production state alongside this work:
- The retired `assembler.inputRewrites` key is removed (the new schema rejects even an empty list); compiler output reaches the assembler unchanged. The earlier interim profile regeneration is retained.
- The production assembler is still the host's GNU as 2.42 until the recipe in section 5 is adopted. Under it, 298 of 2,167 members no longer match. Every one of those is explained by the behaviors in section 2.

The compiler identification this complements is in [compiler-identification-1997-trunk.md](compiler-identification-1997-trunk.md); the method in [compiler-identification-methodology.md](compiler-identification-methodology.md) applies here unchanged.

## 1. Bottom line

- **Identification.** The library assembler is GNU as from the binutils development trunk:
  - Window: ChangeLog dates **1997-02-13** to **1997-04-29**.
  - Configuration: little-endian MIPS **ECOFF** output (`mipsel-ecoff`).
  - The window overlaps the compiler's (1997-02-05 to 1997-03-18), so both tools come from the same few weeks of trunk.
  - It is neither a released binutils nor modern GNU as. The rewrites were approximating two of its behaviors.
- **Verification set.** These are all members whose bytes come from assembler input that a 1997 assembler can read: 161 fully C, plus 17 hand-written `.s`.
- **Byte/relocation result on that set (not full native acceptance).** For all 178:
  - the candidate's section bytes are **byte-identical to the original SDK LNK objects**, with nothing masked, including relocated fields;
  - **all 763 relocations** agree in section, offset, kind and target.
- **Negative control.** Running the same comparison with the 2.8 release flags exactly the six members that 2.8 is known to get wrong.
- **prnt.** `libc2/33-prnt` was parked as MISMATCH in `fa874bb3` ("division-expansion difference"). Its committed draft's instruction bytes match under this assembler. The strict native metadata gate still fails, so its park is not closed by this experiment.
- **No rewrites are needed.** `move` → `addu` and the `.rdata` section name are this assembler's own output.

| Assembler (`-EL -G0 -mips1`) | Fully-C members matched / 161 |
| --- | ---: |
| GNU as 2.42, ELF, rewrites removed | 120 |
| GNU as 2.42, ELF, `move-addu` + `rdata-section` rewrites (previous production) | 160 (prnt fails: division order) |
| binutils 2.6 / 2.7 releases, ECOFF | 140 |
| binutils 2.8 / 2.8.1 releases, ECOFF | 155 |
| binutils 2.9.1 release, ECOFF | 155, and its division order contradicts all 943 originals |
| trunk `tc-mips.c` 1997-02-13 … 1997-04-15, ECOFF (**candidate**) | **161** |

## 2. Whole-population evidence

These censuses need no reconstruction. Each runs over all 2,167 originals (disassembly in `build/assembler-provenance/targets.dis`).

- **`move` encoding.** 10,862 register copies are `addu rd,rs,$zero`; none are `or rd,rs,$zero`.
  - Every binutils from 2.6 to 2.9.1 lists the `addu` encoding first in `opcodes/mips-opc.c`.
  - GNU as 2.42 encodes `move` as `or`. That is what `move-addu` compensated for.
- **Division expansion.** All 943 checked divides use `div $0,a,b; bnez b,1f; nop; break 7`. Signed divides then add the overflow check `li $at,-1; bne b,$at; lui $at,0x8000; bne a,$at; nop; break 6`. None put the branch first with the divide in its delay slot.
  - The branch-first form is "Rework division code to avoid unfilled delay slot" (Jeffrey A Law, ChangeLog Wed Jan 14 1998, commit `6c4b811d6a`).
  - That form is what GNU as 2.9.1 and 2.42 emit, and it is why prnt could not match.
- **Section naming.** `tc-mips.c` names the read-only section by output format: `.data` for a.out, **`.rdata` for ECOFF**, `.rodata` for ELF. This holds in every release from 2.6 to 2.9.1.
  - The originals' `.rdata` (154 members, 40 with switch tables) is therefore ECOFF output, not a Sony renaming. That is what `rdata-section` compensated for.
  - The `.rdata` name alone is weak evidence, because every LNK object, including the ASPSX-native ones, declares `.rdata`. The two points below are stronger.
- **ECOFF section layout in the original bytes.** In an ECOFF relocatable object, sections get consecutive addresses (`.text` at 0, then `.rdata`, `.data`, …), and in-place relocation addends include those addresses. The originals carry exactly that.
  - Example: `libapi/72-counter` `.text+0x1c` is `lw v0,0x174(v0)`, which is `.data`+4 with `.data` placed right after the 0x170-byte `.text`.
  - pcsx-redux's `psyq-obj-parser -c` rewrites such addends to ELF's section-relative form (`lw v0,4(v0)` in `library-input/redux/libapi/72-counter.o`). 236 of the 2,167 converted targets differ from their LNK originals only in this way.
  - An ELF assembler cannot produce the original encoding.
- **Section padding.** All 2,142 non-empty original `.text` sections are multiples of 16 bytes, matching the 16-byte section padding observed in the ECOFF assembler's output.
- **Assembler family.** These were established earlier (`configs/toolchain-identification.md`) and still stand:
  - 455 indexed loads use the GNU as scratch-register rule and none the ASPSX rule;
  - 590 delay slots are filled by reorder-mode swaps.
- **Not evidence.** The converted targets' `e_flags` `0x1000` and their uniform 8-byte section alignment are assigned by the converter.
- **Modern ECOFF is unavailable.** GNU as dropped MIPS ECOFF output in 2.24 ("Remove assembler support for MIPS ECOFF targets", gas NEWS), so no modern build can reproduce it.

## 3. Dating the snapshot

Every behavior that separates the candidates lives in `gas/config/tc-mips.c`.

Its git history (sourceware `binutils-gdb`, pre-1999 CVS conversion) can be trusted file by file. Checked against the official tarballs:
- the revision of 1996-07-03 differs from the 2.7 release's file (mtime 1996-07-04) by 10 lines;
- the revision of 1997-04-30 differs from the 2.8 release's file (mtime 1997-04-30) by 6 lines, an `#ifdef` placement.

Each candidate is the official binutils-2.8 tree with only that file replaced by its revision at a given commit (section 5). Results on the 161 fully-C members:

| `tc-mips.c` revision | Date | Fully-C / 161 |
| --- | --- | ---: |
| binutils 2.7 release | 1996-07 | 140 |
| `c0df26bb95` | 1997-02-12 | 140 |
| `4a1cb5078b` | 1997-02-13 | **161** |
| `a941619c0b` | 1997-03-01 | 161 |
| `18f7e3dc7f` (current at the compiler commit `2b3600acb4ec`, 1997-03-18 18:38 UTC) | 1997-03-16 | 161 |
| `7cd06f4400` | 1997-03-18 | 161 |
| `23ac3ca1f0` | 1997-03-27 | 161 |
| `2f2bcadb7d` (`.set push`/`.set pop` restructure; same file as `acdc7ce30e`) | 1997-03-31 | 161 |
| `3c83da8ac4` | 1997-04-02 | 161 |
| `68952421e6` | 1997-04-15 | 161 |
| `85ce56358f` | 1997-04-30 | 155 |
| binutils 2.8 / 2.8.1 releases | 1997-04/05 | 155 |

Both edges are single upstream changes. The CVS conversion sometimes attaches a file state to a slightly earlier commit, so the dates below come from the ChangeLog of the official 2.9.1 tarball:

| Behavior | ChangeLog entry | Originals |
| --- | --- | --- |
| Hazard `nop`s are emitted tentatively (`prev_nop_frag`) and removed when the following instruction does not need them | Thu Feb 13 1997, Ian Lance Taylor | **present** → lower bound |
| Small-data decision for undeclared externs deferred until after the whole file is read (`nopic_need_relax (sym, before_relaxing)`) | Tue Apr 29 1997, Jim Wilson | **absent** → upper bound |
| Division branch first, divide in its delay slot | Wed Jan 14 1998, Jeffrey A Law | absent |

How each edge shows up in the corpus:

- **Before 1997-02-13.** 21 members fail: `realloc2`, `calloc2`, `malloc3`, `calloc3`, `sprintf` ×2, `qsort` ×2, `bsearch`, `strtoul` ×2, `strtol`, `strcmp`, `strcspn`, `strncmp`, `strpbrk`, `strspn`, `strstr`, `printf`, `prnt`, `s_gtsa`.
  - The assembler keeps hazard `nop`s the originals do not have. Examples: a load-delay `nop` ahead of a branch in `strcmp`, and HI/LO-hazard padding after `mflo` ahead of a jump in `strtoul`.
  - 2.6 and 2.7 fail on exactly the same 21.
- **From 1997-04-29.** Six members fail: `libapi/79-malloc2`, `81-realloc2`, `libc/54-strtoul`, `55-strtol`, `libc2/30-strtoul`, `33-prnt`.
  - Each loads an undeclared external (`_ctype_`, `_AllocRestBlockTop`) through a macro.
  - The macro becomes a relaxable fragment whose form is settled after reading the whole file. The assembler can neither fill a delay slot from it nor drop a load-delay `nop` before it.
  - Examples: `strtoul` gains a `nop` before `lui $at,%hi(_ctype_)`; `malloc2` stops swapping `sw v0,%lo(_AllocRestBlockTop)($at)` into the delay slot of the following `j`.
  - The 2.8 and 2.8.1 releases contain this change and fail on the same six.

The assembler window (1997-02-13 … 1997-04-29) contains the compiler's upper edge (1997-03-18). The tools agree on a single trunk era. The recommended pin is the revision current at the compiler commit's instant (`18f7e3dc7f`). Within the window, every revision gives identical results on this corpus, so the choice is coherence with the compiler, not a measured difference.

Corroboration only, not evidence used above:
- The same history shows Cygnus handling "SCEI PR" reports in 1998, so Sony was a Cygnus customer.
- The compiler's best artifact is Cygnus's CDK tree of 1997-04-04, from the same weeks.

## 4. Verification against the original SDK objects (no ECOFF→ELF conversion)

The SDK's `.LIB` members are SN LNK objects. The section bytes Sony's converter stored in them are the ECOFF assembler's bytes, unchanged; section 2 shows the addends still in ECOFF layout. So the candidate needs no conversion. Its ECOFF sections are compared directly with the LNK records:

LNK record and patch numbers below are decimal.

- **Code and data:** the LNK record 2 (code) payloads per section (record 6 switches section) against the ECOFF section contents, byte for byte.
- **Uninitialized storage:** LNK record 8 (uninitialized data) against the ECOFF section sizes.
- **Relocations:** LNK record 10 (patch) against the ECOFF relocations, compared by section, offset, kind and target. The kind mapping:

  | LNK patch | ECOFF relocation |
  | --- | --- |
  | 16 | REFWORD |
  | 74 | JMPADDR |
  | 82 | REFHI |
  | 84 | REFLO |
  | 100 | GPREL |

  Targets are compared by symbol name (from LNK records 12 and 14) or by section.

Result for the 178 verifiable members: 178 identical, 763 relocations identical. The same check on the 2.8 release's objects reports exactly its six known failures, so the comparison discriminates.

**ECOFF and ELF are two object-file formats:** two ways of packaging the same machine code with section names, symbols and relocations. The project's current oracle compares ELF files because the modern assembler writes ELF. The converted targets in `library-input/redux` are therefore themselves a re-encoding of the originals: their relocation addends were rewritten to ELF conventions. The period assembler writes ECOFF, and modern `objcopy` cannot convert these objects (it stops at their symbol table).

Converting is unnecessary:
- verification can read the original LNK objects directly, as above;
- it compares the original assembler's bytes with the candidate assembler's bytes, with no conversion of either side.

The Redux ELF files remain useful for disassembly and m2c.

## 5. The assembler, reproducibly

**Sources:**
- binutils-2.8, the official GNU release:
  - URL: `https://ftp.gnu.org/gnu/binutils/binutils-2.8.tar.gz`
  - SHA-256: `803733c8f748268875bfea542a55fa7cad24be9fb390d4584939f8122be97379`
  - It is the nearest complete, buildable tree, with files dated 1997-04-30.
- `gas/config/tc-mips.c` at binutils-gdb commit `18f7e3dc7f33dadb4f44259b95dad96785613e50`:
  - fetched from `https://gnu.googlesource.com/binutils-gdb/+archive/<commit>.tar.gz`, a mirror of sourceware's `binutils-gdb.git`;
  - the only edit is removing the Cygnus `start-sanitize-*`/`end-sanitize-*` blocks (16 lines, Toshiba R5900 support), as public releases did.

**Why a hybrid, not the git tree of 1997-03-18.** The git conversion of that era cannot be built:
- `include/` is stale; for example, `include/aout/ar.h` predates its own 1993 ChangeLog entry;
- `bfd/format.c` still uses the 1993 `bfd_error` API;
- 55 source files are missing, including `bfd/corefile.c`, `opcodes/mips16-opc.c` and `gas/sb.h`.

All dated behaviors and both window edges are `tc-mips.c` changes. The remainder of the hybrid is the official 2.8 tree, about six weeks later than the pin: the generic `gas/` core, BFD's ECOFF writer and the opcode tables. On this corpus that difference is not measurable: 178/178 are byte-identical including relocations. If a later member disagreed, those six weeks would be the first place to look.

**Build:**
- Environment: Docker `ubuntu:focal` with `gcc-multilib`, the same as the compiler recipe.
- Compiler flags: `gcc -m32 -std=gnu89 -fcommon -DANSI_PROTOTYPES -w`, linked `-static`.
- Configure: `--host=i386-pc-linux --target=mipsel-ecoff --disable-nls`, then `make all-gas`.
- One host fix: libiberty's own `sys_errlist`/`sys_siglist` declarations are disabled because glibc declares them. Nothing in `gas/`, `bfd/` or `opcodes/` is changed except `tc-mips.c` above.
- The result is `as` with SHA-256 `d4ec93c0236cfa5e7fc8f6258f3345492d9a70a6ece00f19af189f7ed5fa6428`, reproduced byte for byte by an independent rebuild.
- Invocation: `as -EL -G0 -mips1 -I<include dirs> <input> -o <object>`.

**Other built candidates** (same build; hybrids differ only in `tc-mips.c`):

| Artifact | SHA-256 of `as` |
| --- | --- |
| 2.6 release | `4ce522e13a47b9baf16c068bb074330fac3381009c38160017dc6da5d8b0d716` |
| 2.7 release | `713c2c7ba1eab8af0c4f707ca2704c300dc977e5fc5f9b0d7d0a796c86c9a725` |
| 2.8 release | `08dfc945eea2e0ab6eb28fa3f4e52510fab5ce3cb68ee48e88393a9f89a69e02` |
| 2.8.1 release | `0cd49b6b85b376c9fb4ff4cf625d49a61c0d6d8fd2500f84173bf618f775b3ca` |
| 2.9.1 release | `54f78135aa74e15008e0d38da783814aa12f056ae18ced40d09d27e287ef2c81` |
| hybrid `c0df26bb95` (1997-02-12) | `3cd6eaf1302881e4b34b95b436e62382bd47a81c7884f3e851374328e658a1a1` |
| hybrid `4a1cb5078b` (1997-02-13) | `c5acb07493855f47d417387d9245b4c9e499406c03476f7d70033f1f0c6b3f9d` |
| hybrid `7cd06f4400` (1997-03-18) | `55c81f49ae477a41df978f763f4404736948e360573338b313fd7631faf2105e` |
| hybrid `68952421e6` (1997-04-15) | `86158a8cfc7725e3f5cb90b10f8435bc020c24849080db15f05d1fd34d54b140` |
| hybrid `85ce56358f` (1997-04-30) | `9585b5d242ae7a296e03926f513d6e4829b25a20ca55f7f6a5cb1607ba0ab25b` |

Tarball SHA-256s:

| Tarball | SHA-256 |
| --- | --- |
| 2.6 (`.bz2`, sourceware old-releases) | `61dc8824…` |
| 2.7 | `3f336a30…` |
| 2.8.1 | `c7ad94c1…` |
| 2.9.1 | `58d01daa…` |

The full hashes are in `build/assembler-provenance/binutils/tarballs/`. The 1990s releases carry no GNU signatures.

Some older hybrids need compatibility edits, which the recipe does not use:
- `frag_align` two-argument calls given the 2.8 third argument `0`;
- empty `mips_init_after_args`/`mips_frob_file_before_adjust` hooks for revisions that predate them.

## 6. Coverage and limits

- **Verified:** 161 fully-C members and 17 hand-written `.s` members, byte-identical to the LNK originals.
- **608 hand-written `.s` members** do not assemble with any 1997 assembler. They are written for modern GNU as:
  - ABI register names (`$a0`, `$s0`);
  - `include/macro.inc` with keyword macro arguments, `.internal` and `.type @function`.

  This is source syntax, not code. GNU as 2.9.1 accepts more of it and matches 620 of the 625 under a masked comparison. These files need a period-compatible form: numeric registers or a `regdef`-style cpp header, and a `macro.inc` the 1997 assembler reads.
- **1,381 stub-backed C members** are not tested. Their `INCLUDE_ASM` backlog stubs use modern syntax including `.reloc`, and their bytes are copies of the original anyway.
- **All C translation units** also receive `.include "include/macro.inc"` from `include/include_asm.h`. For this experiment it was dropped from fully-C inputs (they contain no other include). Production needs that header to emit it only where `INCLUDE_ASM` is used, or a period-compatible `macro.inc`.
- **ASPSX-built members** are out of scope. The 48 ASPSX-native-style objects are in `Libsn.lib`, which is no longer part of this project.

## 7. Reproduce

Everything below is under the git-ignored `build/assembler-provenance/`:

| Path | Contents |
| --- | --- |
| `binutils/tarballs/` | official release tarballs |
| `binutils/recipe/Dockerfile`, `build.sh` | build environment; `build.sh <label> <target>` |
| `binutils/hybrid.sh` | `hybrid.sh <label> <commit>`: binutils-2.8 with `tc-mips.c` at `<commit>` |
| `binutils/binutils-gdb.git` | blob-less clone used for history and file revisions |
| `binutils/out/` | built assemblers and build logs |
| `scripts/inputs.mts` | regenerates every member's assembler input through the harness `compileSource` |
| `scripts/period_inputs.py` | experiment-only syntax adaptation (section 6) |
| `scripts/period_sweep.py` | masked whole-member comparison against the converted targets; validated against the harness oracle on GNU as 2.42, agreeing on 1,868/299 member for member |
| `scripts/lnk_vs_ecoff.py` | unmasked comparison against the LNK originals, with relocations |
| `scripts/sweep.mts` | strict harness-oracle sweep, with and without the rewrites |
| `no-rewrites/`, `baseline-rewrites/`, `period/` | results |

To reproduce, run from the project root:

```sh
B=build/assembler-provenance/binutils
(cd $B && ./hybrid.sh hpin 18f7e3dc7f && docker build -q -t psx-period-binutils:explore recipe \
  && docker run --rm -u $(id -u):$(id -g) -v $PWD/out:/out -v $PWD/recipe:/recipe:ro psx-period-binutils:explore \
     sh -c 'mkdir -p /tmp/w && cp /recipe/binutils-hpin.tar.gz /tmp/w/ && WORK=/tmp/w sh /recipe/build.sh hpin mipsel-ecoff')
LOADER=$(node -p "require.resolve('tsx', {paths:['../psx-decompilation-harness']})")
node --import "$LOADER" build/assembler-provenance/scripts/inputs.mts .
python3 build/assembler-provenance/scripts/period_inputs.py .
INPUTS=build/assembler-provenance/period-inputs/inputs.json TAG=clean AS_ARGS="-EL -G0 -mips1" \
  python3 build/assembler-provenance/scripts/period_sweep.py . hpin=$B/out/hpin/as-mipsel-ecoff
python3 build/assembler-provenance/scripts/lnk_vs_ecoff.py . hpin
```

## 8. Consequences

1. **A pinned recipe.** Put it next to the compiler's, as `tools/binutils-recipes/<name>/`:
   - a Dockerfile with the two source hashes;
   - the `tc-mips.c` revision and the sanitize step;
   - `expected-as.sha256`;
   - provisioning into `build/dependencies/`.
2. **The harness acceptance path** needs:
   - an assembler that writes ECOFF;
   - verification against the original LNK member, with no conversion;
   - the rewrite code removed.
3. **Hand-written `.s` sources and `include_asm.h`** need the period-compatible form described in section 6.
4. **Superseded:** the `move-addu`/`rdata-section` rewrites (`plans/harness-rdata-section-rewrite.md`) and the "direct GNU as 2.42" base assembler in `configs/toolchain-identification.md`.

## 9. Implemented provenance pipeline and strict-gate results

The shipped recipe is `tools/binutils-recipes/gas-19970318-psx/`. It starts
with the pinned official 2.8 release and reverses every locally verifiable
upstream change, with per-change patches and a per-file manifest. Of 1,285
source files, 1,198 are unchanged, two rolled back and 85 retained with explicit
unverifiable-history reasons. Two clean offline builds reproduce the independent
reference hash `d4ec93c0236cfa5e7fc8f6258f3345492d9a70a6ece00f19af189f7ed5fa6428`.
The installed assembler passes move-as-addu, divide-first and native-rdata tests.
A subsequent fresh download from GNU and clean online Dockerfile replay also
reproduced that exact assembler pin with freshly installed focal dependencies.
The existing hash-enforcing installer installed the byte-identical output;
`build/toolchain-provenance/assembler-online-rebuild/report.json` records input,
recipe and output hashes, with the full build log and prior installation nearby.
All three period programs (cccp, cc1 and as) now have successful online recipe
replays. This is not production activation or original-object acceptance.

The compiler recipe also builds cccp; two clean cccp builds produce
`28b9f74d19c2ec220cce4fe6eec7c71b66380f932427443c9ce3aa393dce9ded`.
All 1,542 C-bearing members reproduce their complete baseline objects with
this preprocessor (zero differences/failures). The owned LF stdarg header
preserves the SDK ABI; immutable DOS headers were not modified.
The complete compiler Docker recipe has subsequently been replayed online,
fetching its pinned public inputs and declared build dependencies. Both rebuilt
programs match their existing pins: cc1
`c4b82c51976e87e365a26c37b8281596e389ec3209ec5a59cd22ec2cf01cc686`
and cccp `28b9f74d19c2ec220cce4fe6eec7c71b66380f932427443c9ce3aa393dce9ded`.
The byte-identical tools and complete 450-file source capture are installed;
the source capture passes the existing compiler-source verification command.
This closes the earlier full-recipe input/replay gap, without claiming that
production cpp/assembler selection or the member-ID migration has occurred.

The harness now reads native LNK/ECOFF directly and compares section names,
kinds, sizes, alignment, every initialized byte (including relocation fields),
relocations and external symbols/COMMON without folding or masking. All 2,167
ELF/original correspondences validate, but **0/178** research candidates satisfy
that full oracle. The earlier 178/178 result above is deliberately narrower.
The former blanket alignment mismatch was a verifier bug, not toolchain
evidence: `readEcoff` assigned BFD's in-memory default 16 despite ECOFF lacking
an encoded per-section alignment field, then compared it with LNK's explicit 8.
That inference is withdrawn. ECOFF alignment is now `null`; required alignment
checks appear separately in `unresolved` and cannot produce MATCH. The same
audit corrected right-first LNK expression operands (important for subtraction
and division); correspondence now rejects `constant - symbol` as a positive
ELF reference. Raw records and full expression trees are preserved, including
`+0`, and all 2,167 correspondences still validate. Original
empty rdata/sdata/sbss declarations are also absent in candidates. These are
reported as declaration differences, not missing initialized storage.

Actual HMD validation uses the original local Sony sources, not reconstructed
assembly: 192/192 compile and agree in initialized bytes and relocation sites
after 915 declared DMPSX replacements. Full native verdict is **0/192** on
metadata. CRLF-to-LF source/header views carry original and view hashes; no
compiler/assembler output is rewritten. The final report also records the
stage implementation and its object-reader dependency hashes; missing stage
implementation fails closed.

All 625 assembly TUs have staged `.ASM` conversions using SDK register/GTE
operations. 623 assemble. Fresh symbolic backlog generation brings the entire
population to 2,160/2,167 compilations, with seven explicit gaps (three sbss
cases and four ambiguous executable-word/data cases). No raw-encoding fallback,
relocation-table copy, synthesized export or target-tail repair was used.
**None** of these candidates is native-exact. The actual staged `check-all`
rejects the first member even though all four instruction words agree.

The full member-ID migration is prepared, including runtime state and attempts;
its write guard refuses without fresh old-ID native matches. Historical references
to the excluded Libsn members have a separate pending, reference-only preparation
based on the archived origin rows and independently hashed original members;
the deleted historical ELF views are not retrospectively certified. The complete
staged preview covers 2,167 active IDs and 4,785 files, including regeneration
of the generated profile rather than text-patching it.

Reports: local `build/toolchain-provenance/{cpp-population/report.json,
correspondence.json,hmd-validation/report.json,period-sources.json,native-gates.json,
alignment-requirement.json}` and the pending migration/reference plans. The
alignment report now explicitly withdraws its former "source-independent
obstruction": that report proved only that an invented reader value caused
rejection, not that the identified tools or source cannot reproduce the program.
The corrected checks separate unavailable metadata from known differences;
no original metadata is copied into a candidate or waived to obtain a match.

A third verifier correction now decodes LNK explicit relocation expressions
and ECOFF in-place addends according to their respective formats, including
section-VMA adjustment and signed HI/LO pairing in table order. It never links,
places sections, changes bytes or folds named references into sections. All
763 research relocations agree. All 178 research objects now have only missing
empty declarations in their known-difference lists; alignment remains
unavailable, and none is accepted. Actual HMD source compilation still agrees
in initialized bytes and relocation sites for all 192 members. Generated
backlog assembly is not independent compiler-identification evidence and is
not counted as recovered source.

Production remains on the interim tool selection. Original inputs, accepted
records, member IDs and autoloop state are unchanged; the loop was not resumed.
The recipes/capabilities are implemented, but the plan's activation requirements
are **not** claimed complete. The last full harness suite has 1,567 tests:
1,444 pass, 123 explicitly skip, zero fail, including the relocation corrections.
The subsequent small input-gp correction also passes the focused native-format
regressions; the full suite was not rerun for that final small edit.
The synthetic native gate test now rejects unproven metadata without writing a
match record, retains byte/relocation evidence and rejects a changed instruction.
Its former positive result depended on the invented alignment and is withdrawn;
the fixture does not certify this SDK.
Original/view changes also invalidate native diagnostic provenance and publication
guards, and source policy checks both original and cpp-expanded assembly.

## 10. Packaging identified; whole-file results (2026-10-18)

The method is in
[assembler-identification-methodology.md](assembler-identification-methodology.md)
(steps 6–8). Evidence is local, under
`build/toolchain-provenance/lnk-encoding-research/`.

**The LNK packaging is a function of the ECOFF object plus constants.**

- **Constant header.** 2,163 of 2,167 members share one header: processor 7,
  then six section declarations, `.rdata .text .data .sdata .sbss .bss`, IDs
  0xF001–0xF006, alignment 8, all declared even when empty. LIBGUN ×2, LIBTAP
  and POWERON share a second header (IDs 0xF000–0xF005, another order). They
  also omit switches for empty sections and are the only members using `.sbss`.
- **Symbol IDs** are the ECOFF external-table index + 1. Nil entries
  (`gcc2_compiled.`, `__gnu_compiled_c`, named statics, labels) consume IDs
  without emitting records. IDs increase in 2,168 of the 2,171 non-Libsn objects.
- **Body.** Sections appear in ECOFF order. Bytes are copied verbatim, ECOFF
  addends included, in BYTES records of at most 0x8000. Patches follow each
  record in relocation-table order. The only expression shapes are `leaf`,
  `leaf + k` and `leaf − k`.
- **Consequence.** The "unresolved alignment" and "missing empty declaration"
  results of section 9 measure the format gap, not the source. An encoder built
  on these rules declares the constants, and a whole-file comparison then checks
  them like every other byte.

**Whole-file results.** An experimental encoder reads only the candidate. Every
result below is whole-file SHA-256 against the original member:

| Set | Whole-file identical |
| --- | ---: |
| HMD validation set (192 ASM sources) | 192/192 |
| Sony's HMD makefiles replayed, ASM objects (with `-D` variants) | 270/270 |
| The same replay, C objects (`-O3`, documented DMPSX C table) | 281/305; the 24 are code differences, see the compiler note §8 |
| Research set (178) | 77; the other 101 differ only in symbol IDs, symbol order or fixup order |
| Staged population: converted assembly (625) | 554; 42 IDs/order only; 27 content (the libgte `smp`/`pmd`/`nmd`/`cmb` set); 2 not compiled |
| Staged population: C (161) | 70; the other 91 differ only in symbol IDs |
| Staged population: backlog stubs (1,381) | 4; 1,183 IDs only; 147 IDs/order + fixup order; 42 content; 5 not compiled |
| LIB v1 archives rebuilt from members and a declared manifest | 22/22 |

**What the symbol IDs reveal.** 825 originals export ID 1 or 2, so their
producer was not GCC (the compiler always emits its two marker labels first):

- 624 are project assembly;
- 88 are project C: every `PSX_BIOS_*` wrapper;
- 113 are backlog.

An ID gap counts named statics: `prnt`'s candidate has three more before `prnt`
than the original. Patch order is gas fixup order: `mtx_006`'s original order
means `la` before `jal` under `.set reorder`.

**Rules still lacking a whole-file witness:**

- **Negative addends.** The period `as` encodes `%hi/%lo(sym-4)` as `(sym − 4h)`,
  the original's shape. All 10 corpus members using negative addends are
  backlog stubs whose generator drops or splits the addend.
- **0x8000 chunking.** The structure is reproduced on both originals that need
  it.
- **The second header.** None of its four members compiles yet.

The acceptance contract built on this (whole-file identity through a declared
`psyq-lnk` stage) is a harness proposal pending approval:
`plans/toolchain-provenance/completion-plan.md`.
