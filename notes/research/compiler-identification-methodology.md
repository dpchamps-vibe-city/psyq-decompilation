# Identifying the compiler behind a binary library: the method

Date: 2026-10-17; steps 8–9 and the later pitfalls added 2026-10-18. This note records *how* the PSY-Q 4.7 library compiler was identified, so the method can be reapplied to another library, another SDK, or a game. The assembler and the object packaging have their own method note: [assembler-identification-methodology.md](assembler-identification-methodology.md). The result itself, with its evidence tables, is in [compiler-identification-1997-trunk.md](compiler-identification-1997-trunk.md); the earlier dead ends are in [realloc3-and-compiler-discovery-session.md](realloc3-and-compiler-discovery-session.md).

## 1. Framing

The question is never "which GCC version string?". It is: which compiler **source state**, under which **target configuration**, with which **flags**, fed to which **assembler**, produced these bytes. Those four axes vary independently, and most false discriminators in the literature (and in this project's own earlier conclusions) come from changing two of them at once. The 2.7.2 verdict of 2026-10-13 compared six compilers at once, and the 2.8.x arms differed from 2.7.2 mostly by a target default (address splitting), not by the version.

Ground truth is the object corpus: 2,224 converted originals. Everything else, including SDK release notes, archive names, version banners, the compilers shipped with the SDK, and prior community attributions, is a lead to be checked against the bytes. Since 2026-10-18 the comparison is against the original LNK members themselves, as whole files, after a declared native-encoding stage. The converted ELF files rewrite relocation addends ([assembler note](assembler-identification-1997-trunk.md) §2), and a whole-file comparison also sees symbol numbering and fixup order, which carry source structure.

A second premise: the project's existing C reconstructions are biased toward whatever compiler they were tuned under. A tuned source failing under another compiler excludes nothing. A tuned source *matching* under a different compiler is strong evidence, and a never-matched member matching from plain C under the new compiler is the strongest evidence of all.

## 2. Steps, as applied

### Step 1: fingerprint censuses over the whole population

Before touching any candidate compiler, measure what the producer did, across all originals, with scripts that need no reconstruction at all (`build/compiler-fit/*.py`). Each census answers one mechanical question and yields a constraint with a known mechanism:

| Census | What it reads | What it constrains |
| --- | --- | --- |
| Return delay slots by frame kind (`return-slot-census.py`) | `jr ra` slot content vs. the preceding `addiu sp` / `lw ra` | Text epilogue (2.7.2 era) vs. RTL epilogue (2.8, enabled 1997-07-11) |
| Global stores (`split-store-census.py`) | `lui $at` macro form vs. compiler-allocated base | Address splitting on or off (unconditional on trunk under `-mgas` from 1996-06-17 to 1997-04-30) |
| Constant re-materialization around calls (same script) | `li aN,K` while a register already holds `K` | Post-reload CSE present or absent (1997-03-26) |
| Jump delay slots (`jump-fill-census.py`) | `j L; <first insn of L>` with the jump redirected past it | reorg fills from the jump's target (1995-12-31), impossible for stock 2.7.2 |
| Frameless functions with several `jr ra` | per-symbol count | `return` insn conversion present or absent |
| Indexed-load scratch register (earlier work) | `$at` vs. destination as temporary | Which assembler expanded the macros |

Censuses are cheap, cover everything, and are independent of the C corpus. They established the lineage (text epilogue, no split, no post-reload CSE, fill-from-target) before any compiler was run, and they are what excluded Homebrew 2.8.1 outright: zero RTL-epilogue shapes among Sony members, six among SN-built libsn.

### Step 2: controlled candidate comparison on the C corpus

`build/compiler-fit/compare.mts` (generalized from the previous session's runner) compiles every C-bearing member under the production compiler and under one candidate, from the **identical preprocessed bytes**, with the production per-TU flags, the production assembler stage, and the whole-member relocatable-object oracle. It records hashes, commands, diagnostics and both objects, and refuses to run if tracked state changes. Options exist to drop a production flag (`--drop-flag=-mgas`), add one (`--alt-flag=-mmips-as`), restrict to a member, or substitute one function's source (`--variant=<member>:<symbol>:<file>`).

Two rules for reading its output:

- Read failures by **mechanism**, not by count. A one-word size change shifts every later word, so "15/136" says nothing; `addrdiff.py` aligns by address and shows the first real divergence. Five of the stock CDK's failures were a single mechanism (reload CSE) and two were another (parameter live length).
- A whole-member verdict is the only acceptance. Function-local comparisons hide neighbor regressions and relocation differences.

### Step 3: use prior work as behavior specifications, not as answers

Three community projects had wrestled with the same objects. DCB's `patch_cc1.py` documents eighteen behaviors it had to binary-patch into stock 2.7.2 to match Psy-Q 4.7 units; Tenchu documents the `lw ra; addiu sp; jr; nop` SDK fingerprint and a block-move split; Tombi and Armored Core document that SN's shipped 2.7.2 builds behave like stock 2.7.2. None of them identified the compiler, but each patch description is a precise, dated behavior. Each one was looked up in candidate sources (`grep` for the function or macro the patch rewrites) and checked present or absent. Thirteen were present natively in the Cygnus 970404 tree; that turned "a patched 2.7.2" into "a 1997 trunk snapshot" as the hypothesis.

### Step 4: date every behavior with the upstream record

GCC's `ChangeLog` files (the complete 2.8.1 tree has them back to 1995) and the gcc-mirror git history date each behavior to a day. A small awk script prints the dated header for every entry naming a function. Building the presence/absence table gives the window directly: present behaviors set the lower bound (`alter_reg`, 1997-02-05), absent ones the upper bound (register-parameter REG_EQUIV, 1997-03-18; reload CSE, 1997-03-26). The GitHub commits API locates the exact commit for a ChangeLog entry (`/repos/gcc-mirror/gcc/commits?path=gcc/function.c&since=…&until=…`), and `codeload.github.com/…/tar.gz/<sha>` fetches the tree at any commit.

Beware of entries that *refactor* a behavior without introducing it (`notreg_cost` was extracted from the `COST` macro on 1997-05-17; the behavior is older), and of behaviors absent from the released tree too (DCB's "combine re-enables volatile MEMs" is not in 2.8.1 either, so it dates nothing).

### Step 5: trace mechanisms in the real binary, then confirm by one-commit reversion

For each discriminating member, find the pass that flips the outcome rather than guessing from the ChangeLog:

- `-da` dumps from the actual candidate binary: `.flow` and `.lreg` list `Register N used M times across K insns`, `.greg` lists the allocation order and dispositions, `.sched` lists life changes. The `first`/`realloc2` swaps were explained by `reg_live_length` doubling (15→30) for parameter pseudos between `.flow` and `.lreg`.
- Static i386 cc1 binaries debug fine under gdb: a hardware watchpoint on `current_function_outgoing_args_size` found the exception unwinder in the pure trunk build in one run; breakpoints found which notes `update_equiv_regs` saw.
- Confirm by reverting exactly one dated upstream commit in a diagnostic Docker build and re-running the corpus. The reload-CSE call disabled: 132→134. The 1997-03-18 commit reverted: 134→137. Each reversion is a hypothesis test, not a product.

### Step 6: reconstruct candidates reproducibly

Every compiler used is built by a Dockerfile from hash-pinned inputs (ubuntu:focal, i386 static, `-std=gnu89`, the decompals/old-gcc conventions). The stock CDK rebuild reproduced the Silent Hill decomp's binary byte for byte, which validated the recipe before any variant was trusted. Two kinds of candidate were built on purpose: the closest real artifact minus later commits (the CDK variants), and a pure dated snapshot from git (the 1997-03-18 trunk). Both reaching 137/137 is what separates "the trunk window" from "something Cygnus-specific".

Git snapshots of 1990s GCC lack build scaffolding (`configure`, `version.c`, `obstack`, generated tables); borrow it from a complete tree of the same era and list each borrowed file. Generate parsers with byacc, as the era's Cygnus Makefile did; modern bison rejects the grammar.

### Step 7: validate out of sample and retire compensations

Three checks distinguish a real identification from a corpus fit:

1. A member no compiler had matched (`libc/48-memmove.o`) matches from ordinary C.
2. The per-TU flag overrides that compensated for 2.7.2 become unnecessary, and the plainer spelling of the rollback helper matches with no flags.
3. The whole `realloc3` member matches with every function in C, including the helper whose tail no earlier compiler could produce.

If a candidate only reproduces the tuned corpus, keep looking.

### Step 8: replay the producer's own build wherever its source exists

Out-of-sample checks on reconstructed C still use sources written under the
candidate. Source the producer wrote is independent of it, so a match there is
the strongest evidence available. The SDK discloses Sony's libhmd sources and
makefiles. Replaying them tests the compiler, flags, preprocessor, assembler,
post-processing and packaging together.

- Parse the producer's makefiles for every listed object: its source, its own
  defines (one source can build several members), its flags and any
  post-processing. Take everything from the recipe; nothing may come from the
  target object.
- Never edit producer sources or headers. Where the host needs it (CRLF, DOS
  upper-case names), compile from views and record both the original and the
  view hashes.
- Compare each object with the shipped member of the same name, whole-file.
  Read failures by mechanism, as in step 2, and separate the causes. A
  difference that no candidate in or around the window changes, and no single
  flag changes, is not compiler-window evidence. Suspect source or header drift
  between the disclosed release and the archive instead.
- The libhmd replay found `-O3` (from the makefile, confirmed by the replay) and
  validated the documented DMPSX C-macro table. It left 24 differences that are
  probably source drift ([result](compiler-identification-1997-trunk.md) §8).

### Step 9: bisect the window with the production recipe

Dating behaviours (step 4) gives a window; building its commits shows whether
anything inside it matters.

- Parameterise the production recipe by commit. First prove the parameterised
  recipe reproduces the pinned binary's hash from the pinned tarball. Otherwise
  a recipe difference can masquerade as a source difference.
- Score every snapshot on two independent suites, holding the preprocessor,
  assembler and flags fixed. Here: the reconstructed members from their staged
  preprocessed inputs, and the producer-source replay. About 30 s per build and
  a few seconds per score.
- An edge is a pair of adjacent commits across which both suites change. Here:
  `4757e6a402f5` → `cabcf079ea40` at the lower edge, and `2b3600acb4ec` →
  `38b610ed8e01` at the upper edge. If the interior is flat, the choice of pin
  inside the window is immaterial for every measured member. Sampled points are
  enough to show flatness, but say that they are samples.
- Unauthenticated, the GitHub commits API allows 60 requests an hour. That is
  enough to list a two-month window at 100 commits per page.
  `codeload.github.com/gcc-mirror/gcc/tar.gz/<sha>` serves any tree.

## 3. Pitfalls met on the way

- **A target default masquerading as a version difference.** Homebrew 2.8.1 "failed" `SpuGetTransferStartAddr` only because it split addresses; with `-mno-split-addresses` it matched. The 1997-04 CDK had no such option at all and splits unconditionally under `-mgas`; `-mmips-as` is the honest way to run it, and is what the producer's configuration must have had.
- **An old trunk default no one remembers.** From 1996-07-23 to 1997-11-26 the trunk's C front end emitted an exception unwinder in every function unless `-fno-exceptions` was given; Cygnus turned it off locally. Without the flag, every function grows a frame and the whole corpus "fails".
- **Scoped closures treated as impossibility.** The previous session's "no clean C witness under 2.8.1" was correct and useless: the compiler was wrong, not the source.
- **Archive and banner provenance.** PSYLIB member timestamps are archive times (2000-02-16), SDK notes name the compilers *distributed*, and `2.7.2.SN.1` is the SDK compiler, not the library compiler. None of it dates a compile.
- **Patching to match.** Binary patches that reproduce an output (DCB) are descriptions of behavior, not identifications, and cannot be adopted as a production compiler. Reversions of dated upstream commits are tests; the production compiler is an unmodified dated source tree plus two build-environment patches that every old-gcc build carries.
- **Comparing unlike containers.** A candidate ECOFF object compared field by field with an original LNK object can never match. LNK declares alignment and six sections that ECOFF does not encode, and a reader's in-memory default (BFD's 16) is not a declaration. Build the original's container with a declared, validated encoding stage and compare whole files.
- **A diagnostic that skips a declared stage.** Diffing pre-DMPSX assembler output against a post-DMPSX original shows false GTE differences. Every comparison must go through the same chain as acceptance.
- **Comparing assembler text across compiler builds.** `-fverbose-asm` writes the compiler's version string into the `.s`, so identical code generation still gives different text. Compare objects.
- **Blaming the pin for a residual.** Before treating a difference as a compiler-window signal, test it at both edges and outside the window. A residual no snapshot changes belongs elsewhere: source, headers or flags.

## 4. Reapplying the method

1. Census the whole population for era-defining shapes (epilogue, address form, delay-slot filling, return conversion, assembler rules). Write down the mechanism and the upstream date behind each shape.
2. Assemble candidates that differ along one axis at a time: same source different flags, same flags different source. Reproduce any published binary before trusting your recipe.
3. Run the corpus runner; read every failure down to its pass with dumps or gdb; date the pass; narrow the window.
4. Build the dated snapshot and test it the same way. Treat equal scores under a real artifact and a pure snapshot as the end of the search.
5. Prove it out of sample: new matches from plain C, retired compensations, whole-member all-C witnesses.
6. Where the producer's source and build recipe exist, replay them through the candidate chain and compare whole files (step 8).
7. Bisect the dated window with the reproducible recipe. Confirm each edge as adjacent commits and check that the interior is flat (step 9).
8. Record hashes of every input, binary and report, and keep diagnostic builds out of production.
