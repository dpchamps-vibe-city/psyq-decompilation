# GNU as, binutils 2.8 rolled back to 1997-03-18

Builds static, 32-bit, little-endian `mipsel-ecoff` GNU as from the official
binutils 2.8 release (`803733c8f748268875bfea542a55fa7cad24be9fb390d4584939f8122be97379`).
The pin instant is the compiler snapshot, 1997-03-18 18:38 UTC. This is an
explicit rolled-back release, **not** a claim that a complete trunk source
snapshot was recovered.

`rollback/manifest.json` accounts for all 1,285 source files in gas, bfd,
opcodes and include, excluding documentation/tests/ChangeLogs. The upstream
window has 213 commits changing 87 files. Two files have verified rollbacks;
85 retain their release content because the local history cannot establish the
required endpoints. Every retained file has its reason and hashes. The MIPS
instruction implementation is rolled back completely, one patch per upstream
change, plus the reviewed six-line release delta. Patch headers retain upstream
commit/ChangeLog text. Source and patch checksum lists are verified during build.

One initially absent intermediate tc-mips.c blob was recovered locally by
partitioning the available endpoint delta and checking the **original Git blob
hash**, `5a92c2490adb266e233a5fb7b0e45ac24994465d`. It is therefore the upstream
blob, not an invented intermediate. No missing source was fetched. A maintainer
can regenerate from an appropriately populated local clone:

```sh
node --import tsx tools/binutils-recipes/gas-19970318-psx/make-rollback.ts \
  /path/to/binutils-gdb.git /path/to/binutils-2.8.tar.gz
```

The generator disables lazy fetching. Missing history is recorded as kept,
never guessed. `sanitize.sh` removes Cygnus sanitize blocks, preserving all
other bytes. The only host fix disables libiberty's duplicate glibc declarations;
no assembler/object correction is made.

## Build and install

Supply the pinned release locally. Prepare a focal build environment with
GCC 9.4 multilib, make, bison, flex, texinfo, m4, patch and perl (the Dockerfile
describes it). Provisioning consumes an installed image, never implicitly pulls
one or fetches source:

```sh
BUILD_IMAGE=your-local-focal-builder BINUTILS_ARCHIVE=/path/binutils-2.8.tar.gz \
  sh tools/binutils-recipes/gas-19970318-psx/provision.sh [--replace]
```

`install.ts` refuses a binary not matching `expected-as.sha256`; it installs to
`build/dependencies/assembler/gas-19970318-psx/as` and writes source, manifest,
recipe, environment and binary provenance. New tooling uses TypeScript rather
than adding a Python installer.

Two independent clean builds in the local focal GCC 9.4 environment produced
`d4ec93c0236cfa5e7fc8f6258f3345492d9a70a6ece00f19af189f7ed5fa6428`, identical
to the earlier instruction-file-only research reference. The move/addu,
divide-first and ECOFF rdata smoke tests pass.

A subsequent clean online replay downloaded the release directly from GNU,
verified its pinned checksum, and built the existing Dockerfile from its pinned
Ubuntu image with freshly installed dependencies. It reproduced the same
assembler hash and passed those smoke checks. The byte-identical tool was
installed with the existing hash-enforcing installer; the previous installation
is retained under `build/toolchain-provenance/assembler-online-rebuild/previous`.
The complete build log and input/output hashes are beside it in `report.json`.
This closes the acquisition/rebuild gap, not the native acceptance gap.

This reproduces the research **byte/relocation** result, not yet the stricter
whole-native-object acceptance contract. LNK encodes section alignment, whereas
ECOFF has no corresponding per-section field; the former verifier incorrectly
substituted BFD's default 16 and called it a mismatch. That claim is withdrawn:
the check is unavailable, not a witnessed alignment difference. Empty section
declarations are also compared explicitly. See the research note and the
harness plan's current progress. Nothing here switches production configuration
or authorizes ignoring differences or accepting unproven metadata.
