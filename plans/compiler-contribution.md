# Plan: contribute the identified SDK compiler and its evidence

Status: proposed, 2026-10-17. Owner: the user. Background:
[the identification](../notes/research/compiler-identification-1997-trunk.md),
[the method](../notes/research/compiler-identification-methodology.md), and the
production recipe in `tools/gcc-recipes/trunk-19970318-psx/`.

Goal: get the compiler that built the PSY-Q 4.7 library objects, a GCC trunk
snapshot of 1997-03-18, into the places the PlayStation decompilation
community already uses, with evidence strong enough that other projects can
retire their binary patches and reconstructed backends.

## 1. Cross-validate on an independent corpus (before anything public)

The identification rests on this project's 137 C members plus three
out-of-sample results. Two other projects reconstructed Psy-Q library objects
and documented what they had to patch; their sources are the cheapest
independent test, and the result is what a reviewer will ask for first.

1. **DCB (ReGame-Labs/dcb_decomp).** Their `src/main/psyq/*.c` cover about
   220 Psy-Q 4.7 objects, each assigned to one of three compiler profiles in
   `config/us/psyq_objects.txt` (patched 2.7.2, patched 2.8.1 with
   `-mno-split-addresses`, and a `-fno-rerun-cse-after-loop` variant). We hold
   the same 4.7 originals, so their C can go through our whole-member oracle
   with the unpatched snapshot. A clone is under the session scratchpad; a
   fresh clone at commit `6c9caf124450cafa1b5f402d03d82b90bb02d16e` is
   equivalent.
   - Map their file names to our members (`libapi_counter` → `libapi/72-counter.o`,
     `libsnd_vs_vtc` → `libsnd/216-vs_vtc.o`, and so on; most map by name).
   - Compile each with our production flags against their headers (they vendor
     `jype0/psyq_headers`); note that their Makefile passes `-mhard-float` to
     Psy-Q units, so measure both float ABIs where it matters (libmath).
   - Record, per object: match or first divergence by mechanism, using
     `build/compiler-fit/addrdiff.py`.
   - Acceptance: their "default" group matches unpatched, or every miss has a
     named mechanism. Their "gcc2.8" group, if it fails as a block, dates the
     second snapshot Sony used; bracket it the same way (ChangeLog dates,
     one-commit diagnostic reversions).
2. **Tenchu (Fuuzetsu/tenchu-decomp).** Their GS_106/107/110/111/113/119/121/
   122/123/125 sources target LIBGS from PsyQ 4.3–4.6. Extract `LIBGS.LIB`
   from the SDK dumps on disk (`Lib44.zip`, `Lib45.zip` under the sibling
   `psyq_sdk` tree), convert with the project's `psyq2elf`, and run the same
   oracle. Of particular interest: GS_107 (their reconstructed backend) and
   GS_119 (reported to need 2.8.x; the 4.7 census found no 2.8-style epilogue,
   so either 4.7 rebuilt it or the report needs the text-epilogue reading).
3. Write the results into `notes/research/` and link them from the
   identification note. Keep diagnostic compiler variants out of production.

## 2. Contribute the recipe to decompals/old-gcc

That repository is where PSX decomp projects obtain compilers, it already
hosts ser-pounce's `cygnus-2.7.2-970404` recipe and an issue about building
from gcc git commits, and our Dockerfile follows its conventions.

- Name: `gcc-trunk-19970318` (not "2.7.2", not "2.8.0"); the banner reads
  `trunk-19970318`.
- Files: the Dockerfile as tracked here (pinned tarball hashes, byacc parser
  generation through `byacc-wrap`, the two old-gcc build patches), the two
  tests, and a README paragraph with the required flags (`-mmips-as`,
  `-fno-exceptions`) and the reason for each.
- State plainly which files come from the Cygnus tarball (listed in
  `install.py`'s `SCAFFOLDING`) and that none of them generates code.
- Offer the expected `cc1` SHA-256 so their CI can assert reproducibility.
- Open the PR referencing the public write-up (step 4) and the cross-validation
  (step 1). ser-pounce is the natural reviewer.

## 3. decomp.me preset

After an old-gcc release contains the compiler, add it to decomp.me's compiler
set and a preset named for the SDK libraries (flags exactly as in
`toolchain.json`, GAS assembler, `-G0`). This lets anyone matching an SDK
object choose the right compiler without rediscovering the flags.

## 4. Publish the finding

- Put the two research notes somewhere linkable (this repository if public;
  otherwise a gist or a page), with the censuses and the compiler-fit reports
  that back the tables.
- Add the compiler to Decompedia's PSY-Q page compiler table with the window
  and the evidence summary.
- Open an issue on dcb_decomp and on tenchu-decomp pointing at the write-up and
  the cross-validation results, since both maintain workarounds this makes
  unnecessary. Credit ser-pounce (CDK source), nocato (Homebrew Psy-Q, whose
  split-address default exposed the first confound), DCB (the behavior
  catalogue), and Tenchu (the epilogue fingerprint).
- Note explicitly what is not claimed: games, other SDK versions, and whether
  Sony's build was Cygnus or FSF.

## 5. Follow-ups in this repository

- If step 1 proves a second snapshot for part of libsnd/libcd/libgs/libc2, the
  harness needs per-member compiler selection; today profiles carry flags and
  assemblers but one `cc1`. Plan that as a harness change before adding a
  second recipe.
- The 141 members with the jump-fill-from-target fingerprint
  (`build/compiler-fit/jump-fill-census.json`) are the next matching targets;
  `memmove` was the first.
- Retire the 2.7.2 bundle (`tools/vendor/gcc/2.7.2-psx`,
  `build/dependencies/compiler/gcc-2.7.2-psx`) once nothing references it; the
  notes keep its hash for history.
- Regenerate or edit the configuration documents that still describe the
  2.7.2 compiler (`configs/project-profile.md`,
  `configs/toolchain-identification.md`).

## Open questions to settle along the way

- The lower bound of the window (1997-02-05) comes from DCB's spill-slot
  observations, not ours; step 1 should confirm or move it.
- Whether `-fno-exceptions` reflects Sony's flags or a Cygnus tree with the
  default off cannot be told from bytes; say so.
- License wording for the old-gcc submission (GPL sources; recipe under the
  repository's terms).
