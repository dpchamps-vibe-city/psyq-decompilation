# trunk-19970318-psx: the production compiler

This recipe builds the compiler that `toolchain.json` selects: GCC's development
trunk as of 1997-03-18 18:38 UTC (gcc-mirror commit `2b3600acb4ec`), the
snapshot family that produced the PSY-Q 4.7 library objects. The identification
and its evidence are in `notes/research/compiler-identification-1997-trunk.md`;
the method is in `notes/research/compiler-identification-methodology.md`.

Inputs, pinned by SHA-256 inside the Dockerfile:

- `https://codeload.github.com/gcc-mirror/gcc/tar.gz/2b3600acb4eceda3000312002ec78fecd5a39d30`
  (the compiler source; everything that generates code)
- `https://github.com/ser-pounce/cdk-gcc/archive/refs/tags/b18.tar.gz`
  (build scaffolding the git history lacks: `configure`, `version.c`,
  `obstack`, the generated keyword table, `getopt`, stab headers, `hash`,
  `tlink`, the i386 Linux host headers; none of it generates code)

Build host: ubuntu:focal, i386 static, `-std=gnu89`. cc1's parser is generated
with byacc through `byacc-wrap`, unchanged. The separate cccp expression parser
uses focal's bison 3.5.1 in yacc mode. `expected-cc1.sha256` and
`expected-cpp.sha256` pin both binaries; `install.ts` validates both before
replacing either installation. The extended recipe installs `cccp` next to cc1
and records both hashes.

Required cc1 flags, already in `toolchain.json`: `-mmips-as` (this snapshot
splits global addresses unconditionally under `-mgas`, which the originals
never show) and `-fno-exceptions` (this snapshot emits an exception unwinder
per function otherwise; the originals contain none).

Provision on a fresh checkout:

```sh
tools/gcc-recipes/trunk-19970318-psx/provision.sh
npm run compiler-source -- verify
npm run analysis-support -- bootstrap
```

`provision.sh` writes `build/dependencies/compiler/gcc-trunk-19970318-psx/cc1`
with its provenance record and `tools/vendor/gcc/trunk-19970318-psx/`
(captured source tree, `upstream.sha256`, a copy of this recipe, `pin.json`).
Both locations are git-ignored, like the previous 2.7.2 bundle.

## Native preprocessor validation (2026-10-18)

Two clean offline cccp-only builds from the existing pinned source capture,
using the focal GCC 9.4 environment, produced
`28b9f74d19c2ec220cce4fe6eec7c71b66380f932427443c9ce3aa393dce9ded`.
The full Docker recipe could not be replayed offline because its acquisition
layers and upstream archives were absent locally; this is not a claim that
cc1 was rebuilt. The existing pinned cc1 remains unchanged. An additional
capture-only cc1 rebuild stopped on missing build inputs (`move-if-change`, then
`cp/lang-options.h`); substituting unrelated compiler headers was not used. Future
recipe exports now retain that helper and the shared `cp/lang-options.h` /
`cp/Make-lang.in` fragments, which the cc1 Makefile needs even for a C-only build.
Those were limitations of the earlier offline attempts. A subsequent full
online Docker replay fetched both SHA-256-checked upstream archives, installed
the declared focal build dependencies (including byacc), and rebuilt both tools.
It reproduced the existing pins exactly: cc1
`c4b82c51976e87e365a26c37b8281596e389ec3209ec5a59cd22ec2cf01cc686`
and cccp `28b9f74d19c2ec220cce4fe6eec7c71b66380f932427443c9ce3aa393dce9ded`.
The export now includes the shared language-option/build fragments and
`move-if-change`. The full replay log and export are retained in ignored
`build/toolchain-provenance/compiler-online-rebuild/`. This closes the full
recipe-replay gap; it does not by itself complete production migration.

The complete 1,542 C-bearing-member population was compiled with the existing
host cpp and then this cccp, keeping cc1 and assembler unchanged. All 1,542
objects were byte-identical (zero differences or compile failures). Two members
initially failed because Unix cccp does not splice the immutable DOS stdarg
header's CRLF continuations. The owned `include/stdarg.h` preserves the SDK ABI
and macro operations with LF endings; the originals were not modified. The two
replays then reproduced their original baseline objects exactly. Full outputs
and hashes are under local `build/toolchain-provenance/cpp-population/`.
Production cpp selection remains part of the gated Phase 6 change, not an
implicit consequence of installing a binary.
