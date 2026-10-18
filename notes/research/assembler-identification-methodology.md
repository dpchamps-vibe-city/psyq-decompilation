# Identifying the assembler and object packaging behind a binary library: the method

Date: 2026-10-18. This note records *how* the PSY-Q 4.7 library assembler, and
the step that packaged its output into SN LNK objects, were identified, so the
method can be reapplied. The results are in
[assembler-identification-1997-trunk.md](assembler-identification-1997-trunk.md).
The compiler's method is in
[compiler-identification-methodology.md](compiler-identification-methodology.md);
its framing and pitfalls apply here too.

## 1. Framing

Three questions, answered by different evidence. Do not let one stand in for
another:

1. **Which assembler** turned compiler output and hand-written text into machine
   code and relocations.
2. **Which configuration**: object format, small-data threshold (`-G`), ISA flags.
3. **Which packaging** turned that object into the shipped container. Here that
   is ECOFF to PSY-Q LNK, done by an unidentified tool whose behaviour is
   recoverable.

Ground truth is the original LNK objects:

- **Not the converted ELF views.** `psyq-obj-parser` rewrote in-place addends to
  ELF conventions; 236 of 2,167 targets differ from their originals only that
  way.
- **Not the SDK's assembler manuals.** ASPSX is what end users ran, which does
  not establish what built the libraries.

**Hold the assembler input fixed.** With the compiler identified, every member's
compiler output is identical across candidates, so only the assembler varies.
Hand-written sources stay a separate population: they test the assembler, not
the compiler.

## 2. Steps, as applied

### Step 1: censuses that need no reconstruction

Run each census over every original, from disassembly alone.

| Census | Reads | Constrains |
| --- | --- | --- |
| `move` encoding | `addu rd,rs,$zero` vs `or` (10,862 copies) | GNU as through 2.9.1 vs 2.42 |
| Division expansion | divide then `bnez`/`break 7` vs branch-first (943 divides) | before the 1998-01-14 rework |
| Read-only section name | `.rdata` / `.rodata` / `.data` | output format (ECOFF names it `.rdata`) |
| In-place addends | relocated fields that include section VMAs (`.data` placed after `.text`) | an ECOFF writer; an ELF assembler cannot produce them |
| Section padding | non-empty `.text` sizes mod 16 (2,142/2,142) | the ECOFF writer's padding |
| Indexed-load scratch register | `$at` vs destination | GNU as vs ASPSX macro expansion |
| Delay slots | reorder-mode swaps | assembler-scheduled code |

### Step 2: candidates along one axis

- **Releases.** Official binutils releases (2.6, 2.7, 2.8, 2.8.1, 2.9.1), each
  built for `mipsel-ecoff` from hash-checked tarballs.
- **Hybrids.** The 2.8 release with only `gas/config/tc-mips.c` replaced by its
  revision at a chosen commit. Every behaviour that separated the candidates
  lives in that file.
- **Check the history first.** Before trusting the git conversion, compare a
  revision with the release that shipped it. The 1996-07-03 revision differs
  from 2.7 by 10 lines; the 1997-04-30 revision differs from 2.8 by 6 lines (an
  `#ifdef` placement).

### Step 3: controlled comparison against the originals

- **Same input, different assembler.** Assemble identical input with each
  candidate. Compare section bytes, unmasked and including relocated fields,
  and decoded relocations, with the LNK records.
- **Negative control.** Run a candidate that should fail: the 2.8 release fails
  exactly its six expected members.
- **Read failures by mechanism.** Do not count them.

### Step 4: date the edges with the ChangeLog

- **Present behaviours give the lower bound.** Tentative hazard `nop`s removed
  when unneeded: 1997-02-13. Before it, 21 members fail.
- **Absent behaviours give the upper bound.** Small-data decisions deferred to
  end of file: 1997-04-29. After it, six members fail.
- **A flat window.** Every revision inside the window gives identical results.
  Choose the pin for coherence with the compiler (the revision current at the
  compiler commit), and say that the choice is not measured.

### Step 5: a reproducible recipe

- **The tree.** Start from the nearest complete official tree (binutils 2.8) and
  reverse every upstream change after the pin. Generate one patch per change,
  carrying its ChangeLog entry.
- **The manifest.** A per-file manifest records each file as rolled back,
  unchanged, or retained with a reason (85 files cannot have their history
  verified).
- **Shared steps.** Apply the release's own sanitize step.
- **Proof of reproducibility.** Two clean builds and a fresh online replay
  reproduce the pinned hash.

### Step 6: identify the packaging step from the originals

1. **Census the container.** Covers header records, section declarations (IDs,
   order, alignment, empty sections), symbol records (order, ID numbering),
   body layout (section order, chunk sizes, where patches go) and patch
   expression shapes.
2. **Separate constants from per-member fields.** Here 2,163 of 2,167 members
   share one header byte for byte: six sections, alignment 8, all declared even
   when empty. A field that is constant across the corpus is a property of the
   tool and carries no source information.
3. **Derive each per-member field from the assembler's object:**
   - LNK symbol ID = ECOFF external index + 1, with Nil entries consumed;
   - section bytes copied verbatim, ECOFF addends included;
   - patches in relocation-table order, with decoded addends;
   - BYTES records of at most 0x8000 bytes.
4. **Build the encoder from the candidate object alone.** It must never read the
   original. It is a declared stage, admitted only after step 7.
5. **The archive** follows the same way. A LIB v1 archive is its members plus a
   declared manifest (names, order, DOS timestamps) plus an export index derived
   from the symbol records. All 22 rebuild byte for byte.

### Step 7: validate whole-file on the producer's own source

- **Replay the producer's makefiles** (compiler methodology step 8): Sony's libhmd
  makefile objects, built by cpp → as → DMPSX → encoder. All 270 ASM objects are
  whole-file identical, and the 192-source validation set is 192/192.
- **Expect the strict oracle to expose reconstructions:**
  - a C reconstruction of an original whose symbol table lacks GCC's two marker
    entries is really assembly (88 members);
  - ID gaps count named statics;
  - patch order is fixup order, which reveals macro and `.set reorder` spellings.

### Step 8: declared stages for named tools that cannot be run

DMPSX converts GTE placeholder words into COP2 commands.

- **Derive the rules from the SDK's own headers and documentation**, never from
  target bytes:
  - the assembly-side table from `INLINE_S.H`;
  - the C-side table from `INLINE_C.H`'s 65 placeholder words, joined with the
    65 rows of the Inline Programming Reference's "DMPSX Inline Function Table";
  - check that entries shared by the two sides agree (17 do).
- **Validate on producer source/object pairs:**
  - 192 ASM sources, 915 replacements;
  - the C-side table made 6 previously blocked objects whole-file identical, and
    gave correct GTE words in 5 more.
- **Fail closed** on any unknown or relocated placeholder.

## 3. Pitfalls met on the way

- **Comparing against converted views.** A converter's addend rewriting makes a
  wrong assembler look right, or a right one look wrong.
- **Comparing unlike containers field by field.** An ECOFF candidate against an
  LNK original cannot be decided for alignment or empty declarations. A reader's
  in-memory default, such as BFD's alignment of 16, invented a universal
  mismatch. Build the original's container and compare whole files.
- **Text rewrites that approximate a tool** (`move-addu`, `rdata-section`). They
  hide the identification. Find the assembler and delete them.
- **Modern tools cannot help.** GNU as dropped MIPS ECOFF output in 2.24, and
  modern `objcopy` stops at the ECOFF symbol table. Period tools must be built.
- **Disassembly-shaped sources.** These produce the right bytes and the wrong
  object:
  - explicit no-reorder spellings change fixup order;
  - included headers that define symbols consume symbol IDs;
  - generators that drop relocation addends (`%lo(DSTACK)` for `DSTACK-4`), or
    split a HI/LO pair across symbols, change bytes and patches.
- **Packaging variants.** Four members use a second header and omit switches for
  empty sections, and they are the only ones that use `.sbss`. That is a
  different encoder version with its own build configuration. Do not force them
  through the main profile.
- **Diagnostics that skip a declared stage.** A pre-DMPSX diff shows false GTE
  differences.

## 4. Reapplying the method

1. Census all originals for assembler-defining shapes (move encoding, macro
   expansions, section names, addend layout, padding, scratch registers).
2. Build candidates along one axis, from hash-checked releases and single-file
   hybrids. Verify git history against release tarballs first.
3. Assemble identical input with each candidate, compare with the original
   objects, and run a negative control.
4. Date the window edges from the ChangeLog. Pin by coherence when the interior
   is flat, and say so.
5. Build a reproducible recipe with a per-file manifest. Reproduce the hash
   twice.
6. Census the container. Separate corpus-uniform constants from per-member
   fields, and derive the fields from the assembler's object.
7. Validate any declared stage whole-file on the producer's own source.
8. Record hashes of every input, tool, stage implementation and report.
