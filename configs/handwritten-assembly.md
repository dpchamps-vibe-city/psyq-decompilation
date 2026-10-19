# Retained handwritten assembly

824 assembly-origin members (866 functions) retain their mechanical assembly
inputs in the repository. A member is assembly-origin when its native LNK object
numbers its symbols from 1, without the two labels GCC puts in every C file;
`split` retains such members automatically and refuses an assembly TU of a
GCC-compiled member. `libpad/20-pdhokres` was the one such case: it was reformed
into a C TU on 2026-10-18 (`npm run library -- reform`).

Hand-written functions inside C members (`asm()` bodies in the original C files)
are retained parts of their C TUs: each carries `"retained": { "kind":
"handwritten-assembly", "evidence": <classifier class>, "originalSha256" }` in
`tu.json`, stays its INCLUDE_ASM extraction and is never a C target. There are
nine: the six BIOS-call helpers of `libapi/73-sc2b` and `_padGunInitHook`,
`_padGunExitHook` and `_padClrHitCount` of `libpad/20-pdhokres`.
`npm run library -- code-classes` is the census and its validation gate.

Each such TU contains:

- `handwritten.ASM`: the unpreprocessed member extraction, copied verbatim;
- `handwritten-symbols.ASM`: its unpreprocessed symbol declarations, copied verbatim;
- `tu.json`: `handwritten.kind: "original-extraction"`,
  `format: "assembler-with-cpp"`, the original object's SHA-256 and both source
  file hashes.

The build generates an include driver under `build/` that places declarations
before the member source. Production CPP expands the retained `.ASM` inputs to
`.s` under `build/`, then the unchanged assembler and declared stages build the
object. Preprocessed `.s` outputs are not source files and are not checked in.
The 1,650 mistakenly retained preprocessed copies have been removed; previously
existing assembly sources were not touched.

These are original-derived assembly, not recovered Sony source. Labels,
instructions and data have not been edited. Do not rewrite the retained files;
hash checks reject changes. `npm run split-all` preserves this representation.
To preview or repeat retention, use
`npm run library -- retain-handwritten [--write] [--json]`. It refuses conflicting
files and leaves C and non-backlog assembly untouched.

Assembly functions remain excluded from the C loop and the graph marks them
`handwritten: "asm"` and `retainedHandwrittenAssembly: true`. The extraction
status `backlog: true` does not claim reconstructed C or recovered assembler
source. It is not a request to translate this assembly.

Every file in a TU directory is listed in its `tu.json`. The unbuilt leftovers
were removed on 2026-10-18: the 88 parked BIOS-wrapper attempts (`.c`,
`_shared-0.h` and the `backlog.ASM` holding an `#if 0` copy of them), the 624
withdrawn agent-written `.s` files, and the `include/library/psx_bios.h` and
`psx_bios_tailjump.h` headers only they used. BIOS calls stay handwritten
assembly and are not translated. All of it remains in git at `0c20c701`.

Whole-object verification checks the retained extraction/build, not recovery
of the original author's source. No compiler or assembler flags, tool binaries,
instructions or labels were changed for retention. C translation continues on
the remaining C stubs.
