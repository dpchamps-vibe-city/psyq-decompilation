# Plan: assembly annotation mode for the autoloop

Status: proposed on 2026-10-15, not started. The manual form of this work is
already in use (see `notes/assembly-splitting-process.md`, step 6); this plan
is what lets the agent loop pick the remaining families up on its own.

## Purpose

625 library members (668 functions) are reconstructed as one-file assembly
translation units and verify byte-exact. They carry Sony's names, the SDK
prototype and argument registers, but 609 of them still have numbered labels and
no comments. The work that makes them intelligible is a per-family *annotation*
pass: a purpose paragraph, a full register table, role-named labels and line
comments, carried from one skeleton to its operand-only siblings. The RotSMD
family (16 members, four skeletons) is the finished model.

Nothing in the loop reaches these members today. `nextTarget` in
`.pi/extensions/psx-decomp/autoloop/oracles.ts` selects graph entries with
`!decompiled && handwritten === false && !dead`; every assembly TU is recorded
as `decompiled: true` so the C queue ignores it. The loop's roles are the prep
tier, the solver tiers and one post-match documentation role
(`documentMatch` in `loop.ts`, tools limited to `DOCUMENTATION_TOOLS`,
skill `psx-post-decompile-documentation`). An annotation role is a fourth kind
of turn, cloned from that one.

## Decisions already taken (project side)

- Header shape, label naming and GTE spelling are settled; the model files are
  `src/libraries/libgte/108-smd_00/smd_00.s` and its 15 siblings, the per-family
  script is `notes/research/asmify/families/smd.py`, the include is
  `include/inline_a.inc`.
- Family notes live in `notes/file-groupings.md`. The 117 generated sections
  follow the ledger parser's convention (`tools/agent/fileGroupings.ts`: a line
  starting with `Members`, then `- <symbol> (m)` bullets), so `siblingsOf`
  resolves a member to its family. Sections written earlier by agents use
  `- Members:` with backticked names and are not parsed; converting them is a
  one-line change per section and is out of this plan's scope.
- Annotation never changes an instruction. The only correctness gate is the
  whole-member oracle (`npm run library -- check --member ID`).

## Design (harness)

### 1. Queue: an `annotated` field on graph entries

`writeLibraryGraph` (`tools/agent/libraryTarget.ts`, where `sourceForm` is set)
computes `annotated` for every assembly-form function from the file:

- the first line starts with `/* ` and names the original library and object;
- no `.L<digits>` label remains in the function's `.ent`/`.end` range;
- at least one instruction line in that range carries a trailing `# ` comment;
- the header has a paragraph between the prototype block and `Register use:`.

`CallGraphEntry` in `.pi/extensions/shared/types.ts` gains `sourceForm` and
`annotated` (both already written by the harness; the extension type does not
declare them). `libraryProgress` prints an annotation line next to the assembly
column: `annotated A/N members`.

### 2. Picker: families, not functions

A new `nextAnnotationTarget(projectRoot, skip)` beside `nextTarget`:

- eligible: `sourceForm === "assembly" && !annotated && !skip.has(name)`;
- unit of work: the family. Resolve the first eligible entry's family with
  `siblingsOf` from the ledger; hand the whole family (all member ids and `.s`
  paths, annotated siblings marked) to one run;
- order: libgte polygon-driver families first (cmb, nom, nmd, pmd, rmd, tmd,
  f3/f4/ft3/ft4/g3/g4/gt3/gt4 and their b/s/m, prs and rmps/rmpr variants),
  then the rest of libgte, singletons, libhmd blocks last. Encode the order as
  a priority on the entry, not as a hard-coded list.

### 3. Role and skill

- `annotate` role: cleared context, tools `read`, `bash`, `edit`, `write` (the
  documentation role's set); no solver tools, no finalize tool.
- Skill `.pi/skills/psx-annotate-assembly/SKILL.md`:
  - read `AGENTS.md`, the family's section in the ledger (grep the heading, never
    the whole file), the model files, and the SDK prototype already in the header;
  - for each distinct instruction stream in the family: read the first member,
    write the purpose paragraph, the register table, the label map and the line
    comments; carry them to operand-only siblings by instruction index, asserting
    the mnemonic at every keyed index as `families/smd.py` does; for edited-copy
    siblings re-place each comment by hand;
  - rename private `func_` and `D_/B_/T_` labels only with evidence from the
    code, in the same pass;
  - never touch an instruction, a directive, a public symbol or the GTE spelling;
  - re-verify every touched member; update the family's Annotation line; stop.
- Prompt in `prompts.ts`: `/skill:psx-annotate-assembly Family: <heading>.
  Members: <list>. Annotation role, not solver role.`

### 4. Gates

- **Bytes**: `library check --member` for every touched member must report
  MATCH; a mismatch restores the file (scope guard snapshot) and parks the family
  with reason `annotation-changed-bytes`.
- **Lint** (new `tools/diagnostics/assemblyAnnotation.ts`, also usable as
  `npm run lint-annotation`): the four `annotated` conditions above, plus: no
  lowercase GTE mnemonic, `.include "inline_a.inc"` present when a GTE command is
  used, every function in `symbols` has a purpose line, no `TODO`/`XXX`.
- **Scope**: allowed writes are the family's `.s` files and
  `notes/file-groupings.md`; `restoreDrift` reverts anything else.
- **Record**: completion under `completions["annotate:<family heading>"]` with
  the member ids, so it never collides with a C completion keyed by function.
- **Commit**: same policy as a match (`commitOnMatch`), message
  `annotate <family>: <n> members`.

### 5. Entry point

`/auto_decompilation_loop annotate [family-heading] [--max=N]` in
`commands.ts` (`parseArgs` gains the mode token), or `"mode": "annotate"` in
`.pi/autoloop.json`. The two queues never interleave in one run.

## Phases

1. Graph field, type, progress line, lint tool (harness; tests on fixtures).
2. Picker and family resolution (tests: a family with one annotated member
   returns the family, not the member; a fully annotated family is skipped).
3. Role, skill, prompt, gates, record, command.
4. Dry run on one small libgte family (f3, 4 members) with `--max=1`; then the
   polygon-driver families; then singletons; libhmd last.

## Tests (harness)

- `annotated` detection on fixture files: unannotated, header-only, fully
  annotated, numbered label left behind.
- Lint rejects: lowercase mnemonic, missing purpose line, missing include.
- Picker: ordering, family grouping through the ledger, skip set, exhaustion.
- Loop: bytes gate parks on a mismatch and restores the file; scope guard
  reverts a C file edit; completion record shape.

## Acceptance criteria

- `npm run progress` shows the annotation count; `npm run graph` entries carry
  `annotated`.
- One loop run annotates a whole family, every member re-verifies, the ledger's
  Annotation line is updated, and nothing outside the allowed files changes.
- A deliberately corrupted family (an instruction edited) is parked, restored and
  reported, never committed.

## Risks

- Edited-copy families (libhmd blocks, cmb, nom, tmd): carried comments can land
  on the wrong instruction. The mnemonic assertion catches shifts; a wrong but
  mnemonic-compatible placement does not. Review the first libhmd block by hand.
- Comment quality is not gated. The lint proves presence, not truth; sample
  families for review before trusting the mode on libhmd.
- Thin-evidence members (the 33 listed in the notes) could later match as C; the
  TU form would switch and comments would have to be carried into the C. Low
  cost, but the picker should not prioritise them.

## Open questions

- Whether private `func_`/`D_` renames belong in this role or in a separate
  naming pass with its own evidence rule.
- Whether to convert the pre-existing ledger sections to the parser convention
  before enabling family deferral in the C loop (it affects both loops).
