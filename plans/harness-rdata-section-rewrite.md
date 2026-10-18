# Plan: let compiler-generated read-only data verify for library members

Status: **superseded 2026-10-17.**
- The rewrite is removed from `toolchain.json`.
- The originals' `.rdata` is the native section name of the ECOFF-writing
  1997 GNU as that assembled them. See
  `notes/research/assembler-identification-1997-trunk.md`.
- The history below is kept for the record.

Former status: implemented and validated, 2026-10-17 (decompilation loop not resumed).
Owner: the user. Decision taken: fix it with an assembler-input rewrite in the
harness (`../psx-decompilation-harness`), not with a section-name alias in the
oracle. Background: the sprintf assessment of
2026-10-17 (session notes below), the loop's draft `build/sprintf_draft_v32.c`,
and its measurement under
`build/pipelineReversal/libc_46::sprintf/objective/measurement-JSpEhI/`.

Goal: a library member whose original carries a `.rdata` section (string
tables, constant arrays, switch jump tables) can reach a whole-member MATCH
from C, and the residual objective stops reporting the section's name as a
source difference.

## Implementation and validation (2026-10-17)

- Steps 1–5 and 7–9 are complete. The runtime closed set and editor schema
  accept `rdata-section`; the compiler-input rewrite preserves comments, line
  count and endings and respects the existing handwritten-input/`#APP` guards.
  No oracle, residual-objective or executable-project setting was changed.
- Focused assembler, cache-identity and library-TU tests: **23 passed**. Coverage
  includes both rewrite selections, CRLF/no-final-newline input, excluded
  syntax/handwritten input, allocated PROGBITS and relocations, merging with
  included data, and compilation-identity invalidation.
- `npm run check-all`: **2,224/2,224 members byte-exact**. Assembly backlog remains
  backlog, not reconstructed C. `run_output/autoloop/state.json` is unchanged.
- The full harness suite reports **1,417 passed, 122 skipped, 9 failed**. All nine
  failures were reproduced without this change in an isolated baseline retaining
  the harness's pre-existing working-tree edits; they are not resolved here.
- Sprintf v32 was measured in an isolated project under
  `build/rdata-section-validation/project`, with all data defined in C before the
  function, SDK `stdarg.h`/`string.h`, and no data stub. The production assembler
  emits `.rdata` of size `0xe0`, no `.rodata`; `.data` and the two digit strings
  are identical to the original. Only the 45 relocated jump-table words differ
  in `.rdata`. The whole-member differences are `.text` bytes, `.rdata` bytes
  and symbolic relocations, as expected for the unfinished draft. The residual
  objective's instruction-population site names neither section.
- Evidence and replay driver: `build/rdata-section-validation/validate.mts`,
  `sprintf.json`, `sprintf-objective.json`, `summary.json`, `focused-tests.log`,
  `harness-tests.log`, `harness-baseline-tests.log`, and `check-all.log` in that
  directory. No production C was edited. The optional preparation-packet hint
  (step 6) was deferred; step 10 remains the subsequent decompilation task.

## 1. Problem statement

The whole-member verdict for a library member comes from
`compareRelocatableObjects` (`tools/lib/relocatableObject.ts`). It pairs the
original's program sections with the candidate's **by exact name** and reports
any name present on one side only as "program storage kind/size differs or
section missing". The per-function view (`relocatableFunctionOracle.ts`), the
finalize gate and the autoloop all sit on top of that verdict.

The production compiler (GCC trunk 1997-03-18, `-mmips-as`) emits the MIPS
assembler directive `.rdata` for read-only data: string literals, `static
const` arrays, and every switch jump table (`.rdata` / `.align 3` / `.word
$L..`). Modern GNU as on an ELF target spells that section `.rodata` (the
`.rdata` pseudo-op maps to `RDATA_SECTION_NAME`, which is `.rodata` for ELF).
The originals, SN objects converted by `tools/psyq2elf-redux`, carry the
Psy-Q name `.rdata`, and the library disassembler preserves it by writing an
explicit `.section .rdata, "a", @progbits` (comment in
`tools/lib/libraryAssembly.ts`: "GAS does not infer allocation for PSY-Q names
such as .rdata").

So any candidate that produces read-only data from C gets a `.rodata` section
the original does not have, and lacks the `.rdata` the original has. No C
spelling can change a section name. The consequences, measured on 2026-10-17:

| | count |
| --- | --- |
| originals with a non-empty `.rdata` section | 154 of 2,224 |
| of those, with a switch jump table (`.rdata` words relocated against `.text`) | 40 |
| of those ever matched from C | 0 |
| members with a `_data.c` part | 277 |
| `_data.c` parts converted from `INCLUDE_ASM` to C | 0 |

`libc_46::sprintf` is the first attempt at any of them. The
solver converged from 474 to 496 of 539 words in 32 drafts, but its candidates
carry **both** sections: the compiler's tables in `.rodata` and the original's
tables in `.rdata`, pulled in by the still-stubbed `_data.c`. Even a perfect
text match will read MISMATCH, `finalizeWorkspace` will refuse it, and the
autoloop will park the function as "needs harness repair" (compare the parked
`libapi_73::func_0000031C` in `run_output/autoloop/state.json`).

The residual objective makes it worse: its instruction-population site lists
`lui/addiu %hi/%lo(.rdata@0)` as target-only and `(.rodata@0)` as
candidate-only and tells the solver "the source computes something the target
does not". Five of the six "target-only" shapes in the v17 measurement were this
artifact.

## 2. Context: the executable path already solved this

`tools/lib/functionOracle.ts` (executable containers) relocates the candidate
against splat's section bases and aliases the names both ways, with the comment
"cc1 emits `.rdata`; splat names the same subsegment `.rodata`". It also warns
when a candidate emits a jump table and splat has no `.rodata, <function>`
subsegment. Preparation collects `jtbl_*` symbols from splat's data assembly
for m2c. None of that reaches the library path, which compares relocatable
objects directly and had never been asked to verify read-only data. Nothing in
the executable path needs to change.

## 3. Evidence the rewrite is sufficient

Scratch experiment, 2026-10-17, on draft v32 with the data defined in C
(`static FmtSpec D_000009F0 = {0};`, the two digit tables as `static const`
arrays, no `_data.c` stub), compiled with the configured cpp/cc1 flags and
assembled through `assemble()` from `tools/lib/assembler.ts`:

| candidate | sections | oracle differences |
| --- | --- | --- |
| compiler output as emitted | `.text .data .bss .rodata` | `.text` bytes; `.rdata` missing; `.rodata` missing; relocations |
| same assembly, the two `.rdata` directive lines spelled `.section .rdata,"a",@progbits` | `.text .rdata .data` | `.text` bytes; `.rdata` bytes (jump-table entries only); relocations |
| original | `.text .rdata .data` | |

With the spelling fixed, section names and sizes agree (`.rdata` 0xe0, `.data`
0x10). The two strings at `.rdata+0x0` and `+0x14` are byte-identical, the
45-entry table starts at `+0x28` under the compiler's own `.align 3` exactly as
in the original, and `.data` is the same 16 zero bytes. The only `.rdata`
differences are table entries that follow text offsets, which move as the text
converges. The compiler-side mechanics of jump tables (the table shape, the
`lw $2,table($2)` macro expanding to the original's `lui/addu/lw $at`
sequence) need no work.

GCC's other section directives are not affected: `.text`, `.data` and `.sdata`
keep their names under GNU as, `.lcomm`/`.comm` land in `.bss`/COMMON as the
originals do. Section census of the originals: `.text` 2188, `.data` 181,
`.bss` 51, `.rdata` 154, `.sbss` 4, `.sdata` 2. `.rdata` is the only name GNU
as rewrites.

## 4. Design

Add a second named rewrite to the closed set in `tools/lib/assembler.ts`:

- ID: `rdata-section`.
- Match: a compiler-emitted directive line that is exactly `.rdata`, with
  optional surrounding whitespace, an optional trailing `#` comment and an
  optional `\r`. Replace the directive with `.section .rdata,"a",@progbits`,
  retaining the comment and the line ending. Line count is unchanged.
- Not matched: labels (`rdata:`), operands (`.word rdata`), `.rdata` with
  arguments (GCC never emits any), `.data`, `.text`, `.sdata`, and anything
  inside `#APP`/`#NO_APP` or in a handwritten assembly TU. The existing
  `rewriteAssemblerInput` already skips `#APP` regions, and
  `assemblerInvocation` skips rewrites entirely for `handwritten` inputs.
- Flags `"a",@progbits` are what the library disassembler writes for the
  original's `.rdata`, so compiler output and any still-stubbed `INCLUDE_ASM`
  data merge into one section with the same storage kind.
- Opt-in per project through `assembler.inputRewrites` in `toolchain.json`,
  like `move-addu`. This library project enables it. Executable projects keep
  their current list: their oracle aliases the names, and their linker scripts
  collect `.rodata`.

Why not alias in the oracle instead: an alias fixes the verdict only. The
produced objects would still be named unlike the SDK's, the residual
objective's naming artifact would remain, and the finalize receipts would need
a third place to agree. The rewrite fixes every consumer at the source, and it
is the same mechanism the project already trusts for `move-addu`.

## 5. Steps

### Harness (`../psx-decompilation-harness`)

1. `tools/lib/toolchain.ts`: add `"rdata-section"` to `ASSEMBLER_REWRITES`.
   The closed-set validation at load time then accepts it and still rejects
   unknown IDs.
2. `tools/lib/assembler.ts`: implement the rewrite in `rewriteAssemblerInput`
   next to `move-addu`, keeping the per-line structure, the `#APP` guard and
   the "unknown rewrite" error. Add it to the `AssemblerRules` documentation
   comment if the rules table is where such behavior is described.
3. `tools/lib/assembler.test.ts`:
   - Extend the GAS rewrite fixture with a `\t.rdata # comment\r\n` line, a
     `.rdata` line inside `#APP`, a label `rdata:` and an operand `.word rdata`;
     assert only the first is rewritten, the line count is unchanged, and
     `rewriteAssemblerInput(text, [])` is the identity.
   - Add an end-to-end case: assemble a snippet containing `.rdata` /
     `.align 2` / `.word label` with the rewrite enabled and check through
     `readRelocatableObject` that the object has `.rdata` (PROGBITS, alloc)
     and no `.rodata`; without the rewrite it has `.rodata`.
   - The configuration test's list of accepted selections gains
     `{ kind: "gas", inputRewrites: ["move-addu", "rdata-section"] }`.
4. `docs/toolchain.md`: a paragraph after the `move-addu` one. The
   original-word evidence the doc demands is the census above: 154 originals
   carry `.rdata`, the converter and `libraryAssembly.ts` keep that name, and
   the directive the compiler emits is renamed only by the assembler.
5. Residual objective (`tools/agent/residualObjective.ts`): no change expected,
   because section names in its population summaries come from the oracle's
   relocation references. After step 7, confirm on sprintf that the
   `.rdata@0` versus `.rodata@0` entries are gone. If any library-side code
   hardcodes `.rodata` (none found on 2026-10-17), fix it there.
6. Preparation hint (optional, `tools/agent/prepareFunction.ts` or the library
   preparer): when the member's original has `.rdata` or `.data`, say in the
   prepared context that the compiler must produce it (strings, tables, jump
   tables, initialized statics), that definitions feeding `.rdata` must precede
   the function so the jump table lands after them, that `_data.c` must be
   converted in the same change, and that symbol-less originals need `static`.
   The calloc3 and sprintf sessions both lost time to exactly these points.

### This repository

7. `toolchain.json`: `"inputRewrites": ["move-addu", "rdata-section"]`.
   Regenerate `configs/project-profile.md`
   (`node tools/harness-proxy.mjs tools/build/genProjectProfile.ts --write`)
   and update the base-assembler line in `configs/toolchain-identification.md`.
8. `npm run check-all`. Expected: 2,224 of 2,224 byte-exact, unchanged. The
   rewrite is a no-op for every member matched today (no matched member's
   compiler output contains `.rdata`, and handwritten TUs skip rewrites). The
   assembler selection is part of the compilation identity, so receipts are
   re-verified rather than reused; budget the full run.
9. Validation on sprintf, before resuming the loop: compile a draft that
   defines the data in C, assemble through the production path, and run the
   whole-member oracle. Acceptance: the differences list contains only `.text`
   entries plus `.rdata` words that are jump-table entries; `.data` and the two
   strings are byte-identical; the residual objective's population site no
   longer names either section. The scratch driver in the appendix does this
   without touching production files.
10. Resume `/auto_decompilation_loop` on sprintf. After it finalizes, the 39
    other jump-table members and the rest of the 154 become reachable, starting
    with the twins and relatives: `libc2/34-sprintf`, `libc2/33-prnt`,
    `libmath/56-printf2`, `libgpu/2-kprintf`.

## 6. Data-part conventions the first conversion must settle

The TU driver includes parts in manifest order: `_shared-0.h`, the function
parts, then `_data.c` last. Emission order in the assembly follows source
order: a file-scope static is output at its definition, a string literal
before the function that uses it, a jump table while the function is output.
For sprintf the original `.rdata` is strings (`+0x0`, `+0x14`) then the table
(`+0x28`), so the tables must be defined **before** the function: as file-scope
definitions in `_shared-0.h` (the TU model already keeps file-scope data in
shared fragments) or as string literals inside the function. `.data` has a
single object here, so its definition can live anywhere, including `_data.c`
with a tentative declaration ahead of the function.

Rules that fall out of the experiment and the calloc3 episode:

- A zero-initialized static with an explicit initializer (`= {0}`) goes to
  `.data` under this compiler; with no initializer it goes to `.lcomm`/`.bss`.
  The original's 16 zero bytes in `.data` need the explicit form.
- Objects the original exports no symbol for must be `static`; the symbol
  population is part of the verdict.
- `_data.c` ends as a C part with no `INCLUDE_ASM` (a comment, or the `.data`
  definitions). A function part may only define its function; data belongs in
  the shared fragments or the data part.
- While `_data.c` is still assembly, the compiler must emit no `.rdata` at
  all, or the merged section doubles in size. That mismatch is the correct
  signal, but the message will read "size differs"; the preparation hint in
  step 6 is what tells the solver why.
- GNU as pads section sizes to 16 bytes for this target, which is what the
  originals show (`.data` 12 bytes of content, 16 on disk).

Unrelated to sections but worth settling in the same pass: the v32 draft
`#undef`s `va_arg` and substitutes a GNU statement-expression macro. The TU's
real header is the SDK's converted `library-input/converted/include/stdarg.h`,
whose post-increment form should fold to the original's load-then-increment
sequence. Prefer the header; the clean-source gate may reject the override.

## 7. Risks

- A member that needs `.rdata` while its `_data.c` is still assembly cannot
  match in that transitional state (duplicate content). That is inherent, not
  a defect of the rewrite; the fix is converting the data in the same change.
- Changing `inputRewrites` changes the compilation identity; expect every
  receipt to be recomputed once. Check that `run_output/autoloop/state.json`
  completions are re-validated, not discarded.
- Executable projects must not copy the setting without checking their linker
  script collects `.rdata` as well as `.rodata`.

## Appendix: scratch driver used for the evidence

Run from the project root with the harness's `tsx`
(`../psx-decompilation-harness/node_modules/.bin/tsx driver.mts <scratch-dir>`),
where `<scratch-dir>/tu.c` includes `_shared-0.h` and a draft that defines the
member's data in C. It drives the configured cpp, cc1 and `assemble()`,
compares as-is, then rewrites the `.rdata` directive lines and compares again.

```ts
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { join } from 'node:path';
import { spawnSync } from 'node:child_process';
import { createRuntimeContext, inRuntimeContext } from '../psx-decompilation-harness/tools/lib/runtimeContext.ts';
import { withLibraryMetadata, libraryMembers } from '../psx-decompilation-harness/tools/lib/libraryTargets.ts';
import { withContentMemo } from '../psx-decompilation-harness/tools/lib/contentCache.ts';
import { libraryContext } from '../psx-decompilation-harness/tools/lib/project.ts';
import { configuredTool, configuredFlags } from '../psx-decompilation-harness/tools/lib/toolchain.ts';
import { assemble } from '../psx-decompilation-harness/tools/lib/assembler.ts';
import { compareRelocatableObjects } from '../psx-decompilation-harness/tools/lib/relocatableObject.ts';

const root = process.cwd(), S = process.argv[2], id = 'libc_46';
const run = (exe: string, args: string[], cwd: string) => { const p = spawnSync(exe, args, { cwd, encoding: 'utf8' }); if (p.status !== 0) throw new Error(p.stderr); };
inRuntimeContext(createRuntimeContext(root), () => withContentMemo(() => {
  const members = libraryMembers(root);
  withLibraryMetadata(() => {
    const member = members.find(m => m.id === id)!, ctx = libraryContext(id);
    const out = join(S, 'out'); mkdirSync(out, { recursive: true });
    run(configuredTool('cpp'), [...configuredFlags('cpp', ctx), join(S, 'tu.c'), '-o', join(out, 'tu.i')], root);
    run(configuredTool('cc1'), [...configuredFlags('cc1', ctx), 'tu.i', '-o', 'tu.s'], out);
    assemble(ctx, join(out, 'tu.s'), join(out, 'tu.o'), root);
    console.log('as emitted:', compareRelocatableObjects(member.bytes, readFileSync(join(out, 'tu.o'))).differences);
    const asm = readFileSync(join(out, 'tu.s'), 'utf8').replace(/^[ \t]*\.rdata[ \t]*$/mg, '\t.section .rdata,"a",@progbits');
    writeFileSync(join(out, 'renamed.s'), asm);
    assemble(ctx, join(out, 'renamed.s'), join(out, 'renamed.o'), root);
    console.log('rewritten: ', compareRelocatableObjects(member.bytes, readFileSync(join(out, 'renamed.o'))).differences);
  }, members, root);
}));
```
