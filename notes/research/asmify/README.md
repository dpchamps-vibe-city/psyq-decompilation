# asmify: hand-written members -> natural gas source, byte-verified

`asmify.py` reads `build/libraries/disassembly/<member>/member.s` for every member listed in
`asm_members.json` (the 625 members classed as hand-written assembly), writes a natural `.s`
(gas macros, local labels, no spimdisasm artifacts), assembles it with the project toolchain
flags, and compares the object against `build/libraries/originals/<member>/*.o`.

Run from the project root: `python3 notes/research/asmify/asmify.py [tu-dir-suffix ...]`
Outputs: `build/asmify/out/<lib>/<tu>/<name>.s`, `build/asmify/results.json`.

Two source forms are tried. Reorder mode (nops dropped, slot instructions hoisted; gas
re-derives hazards and fills slots) is kept only when it reproduces the bytes with no
`.set noreorder` island; otherwise the whole-file `.set noreorder` form with explicit nops is
written, which is the form the bytes themselves point to for libgte/libhmd.

Comparison is the harness comparator (`tools/lib/relocatableObject.ts`) plus one
canonicalisation: a relocation against a symbol defined in the same object is compared as
section + (symbol value + addend). gas emits symbol relocations for globals, the converted
originals are section-relative; both link to the same bytes. 14 members need this; the
harness comparator now performs the same fold itself (`canonicalizeDefinedReferences`),
so all 625 verify under `npm run check` directly.

`import.py` installs the outputs as assembly translation units: it replaces each member's
stub parts with `<name>.s` and rewrites `tu.json` to the one-part form
`{ "path": "<name>.s", "symbols": [...] }` that the harness assembles and verifies. It is
idempotent and refuses to replace real C except for the members it lists explicitly.

## Annotation conventions (settled 2026-10-15)

The installed `.s` files are source, and readability work on them never touches an
instruction: the oracle compares bytes, relocations and public symbols, so comments, `.L`
label names and local data labels are free to change (`npm run check-all` confirms).

- **GTE spelling**: `include/inline_a.inc` defines the GTE commands under the names and
  parameter order of Sony's `INLINE_A.H` (`RTPT`, `NCLIP`, `MVMVA sf,mx,v,cv,lm`, ...),
  assembling the real coprocessor-2 words gas needs instead of the DMPSX placeholders.
  Hazard nops stay written out as the bytes place them; the `n`-prefixed forms are not
  reproduced (gas macro names are case-insensitive, so `nOP` would capture every `nop`).
- **Header shape** (model: `src/libraries/libgte/108-smd_00/smd_00.s`): original library
  and object name, the SDK prototype of every function, one paragraph of purpose, then a
  `Register use:` table.  `annotate.py` generates the mechanical part (prototype from the
  SDK headers, argument registers and entry stack offsets, the decoded HMD unit type for
  `GsU_` drivers); the purpose paragraph and the remaining register rows are added by hand.
- **Labels**: role names (`.Lnext`, `.Lreject`, `.Ldone`), never numbers.
- **Family notes** live in `notes/file-groupings.md`; `groupings.py` generated the initial
  section per family (objects, targets, shared instruction structure, hand-written
  evidence, verification, annotation status).  Agents update the Annotation line there.

`python3 notes/research/asmify/annotate.py [--dry-run] [lib/tu ...]` is idempotent: files
whose first line already starts with `/* LIB` keep their header and only get the spelling pass.

`families/smd.py` is the worked model of a per-family semantic pass (RotSMD, 16 members):
each of the family's four instruction-stream classes gets one purpose paragraph, one register
table, one label map and one comment map keyed by instruction index; the script asserts the
mnemonic at every keyed index and the variant's tag constant before writing, so a sibling
whose stream drifted from its class fails loudly instead of receiving wrong comments.
