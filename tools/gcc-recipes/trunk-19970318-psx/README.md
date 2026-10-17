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

Build host: ubuntu:focal, i386 static, `-std=gnu89`, parsers generated with
byacc through `byacc-wrap`. The expected `cc1` hash is in
`expected-cc1.sha256`; `install.py` refuses anything else.

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
