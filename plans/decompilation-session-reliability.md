# Plan: improve decompilation-session reliability for library targets

Status: proposed; report and implementation plan only. No harness changes implemented.

Source session:
`/home/dave/.pi/agent/sessions/--home-dave-Documents-code-psyq-decomp--/2026-10-21T01-44-54-219Z_01a15c21-feca-736d-ad68-d801a1984a68.jsonl`

Recorded interval: 2026-10-21, approximately 01:45–02:35 UTC.
Line references below are physical lines in that JSONL, not generated artifact lines.

## Executive summary

The session spans approximately 50 minutes and five functions, with 84 calls to
`psx_residual_objective` and 524 shell calls. Two functions pass finalization.
The unfinished work combines real legacy-compiler matching difficulty with
broken or unsupported library diagnostics, a concrete function-discovery/split
blocker, and weaknesses in the agent's interpretation and retention of evidence.

The most actionable finding is not a difficult C reconstruction: `DsQueueLen`
is a four-instruction function whose inferred extent absorbs three independent
callbacks. The current split requires those callbacks' bytes while rejecting a
candidate that defines them alongside the selected function.

The controller compounds this by rejecting the agent's parking request and then
sending a generic instruction to write a body, despite a preserved candidate and
an evidence-backed blocker report.

**Parking decision:** allow the agent to request parking during an active
escalation campaign. Persist a function-level park only at the final rung of the
configured escalation ladder. At an earlier rung, process the request as a normal
handoff to the next rung, without marking the function parked.

## Outcomes in the recorded session

| Function | Recorded outcome |
| --- | --- |
| `libds_1::DsPacket` | Verified exact, including finalization gates. |
| `libds_1::_DsPacket2` | Approximately 30 minutes of work; 57 objective calls and drafts through `v61`; not exact. |
| `libds_1::DsSync` | Substantial structural improvement, but not exact; population differences remain. |
| `libds_1::DsReady` | Verified exact, including finalization gates. |
| `libds_1::DsQueueLen` | Function-discovery/split blocker; no verified match. |

These are outcomes as of the supplied log, not a fresh verification of the
current working tree. The log ends during an aborted, unfinished experiment.

## Findings

### A. Preparation supplies broken or incomplete starting material

- `DsPacket`'s generated draft passes four arguments to `_DsPacket2`; the original
  calling sequence passes six.
- Including `<libds.h>` conflicts with declarations already present in the
  reconstructed TU, notably the `DsCommand` typedef/function name collision.
- Other drafts contain unresolved `?` types, invalid field accesses, duplicate
  typedefs, or incompatible declarations.
- `_DsPacket2` receives no generated body because m2c cannot recognize its jump
  table, even though the original object contains the table.

The handoffs report these failures honestly. Nevertheless, the solver spends
substantial effort repairing signatures, declaration ownership, and control flow
before it can perform a meaningful matching experiment.

Evidence: lines 6–30, 38–55, 827–855.

### B. Library diagnostic support is incomplete end to end

Observed failures:

| Diagnostic | Observed result |
| --- | --- |
| Reconstruction engine | `ET_REL symbolic storage/callee relocation execution is not implemented`; zero candidates evaluated. |
| Family transfer | Searches for `target_path` / a PS-X EXE rather than adapting the library target. |
| Near-miss repair | Explicitly rejects relocatable-library targets. |
| Explain-diff | Invokes `objdump` on an unrecognized candidate object format. |
| Inventory / allocator diagnostics | Repeated `Native target changed` failures involving generated candidate paths. |

Some deeper diagnostics also require live C rather than accepting the scratch
candidate. The agent temporarily integrates nonmatching C to unlock them, only
to encounter another diagnostic failure.

These observations do not establish why every mutation guard fired. Investigate
those failures independently rather than assuming that an original input really
changed or disabling the integrity check.

Evidence: lines 173, 181, 538, 590, 632–634, 927–945.

### C. `DsQueueLen` is assigned other functions' bytes

The intended function is a global load and return: four instructions, 16 bytes.
Its size-zero original symbol is assigned an inferred extent of `0x1c0` bytes.
The extra `0x1b0` bytes belong to three independent callback functions at section
`.text` offsets `0x1240`, `0x12e4`, and `0x13b8`.

Their addresses are passed to callback registration functions with this pattern:

```asm
lui   a0,%hi(callback)
jal   DS_ready_callback
addiu a0,a0,%lo(callback)   # call delay slot
```

The discovery implementation printed in the session has two relevant obstacles:

1. `publishedAddress()` scans forward from the LO16 instruction, missing the
   preceding call that consumes the address after its delay slot executes.
2. The HI16/LO16 pairing logic treats a control transfer between the two halves
   as a clobber, even in this valid call-delay-slot formation pattern.

Fixing only the forward scan would therefore not address the entire path.

The resulting contradiction is witnessed by production tools:

- A source defining only `DsQueueLen` omits the callbacks and fails whole-member
  identity.
- A source also defining the callbacks is rejected with
  `DsQueueLen.c: must define only DsQueueLen`.
- Omitting the callbacks changes section layout. The global load's differing
  encoded low half changes by exactly `0x1b0`, consistent with the missing code.

The agent calls the function itself solved, but that is stronger than the
verification permits: neither a complete member match nor successful
finalization is demonstrated. The structural blocker is well supported.

Evidence: lines 1096–1198, 1250–1256, 1270–1290.

### D. `_DsPacket2` has a real compiler-matching residual

The agent successfully recovers the switch, duplicated case bodies, helper-call
boundaries, unaligned location copy, and much of the loop structure. A
pointer-based loop improves the result substantially over indexed forms.

It then stalls on loop-pointer initialization, constant folding, copy
elimination, scheduling, and register allocation. A representative difference:

```asm
# Target derives a field pointer from another register:
addiu field_ptr,base_ptr,12

# Candidates often fold it into a direct stack address:
addiu field_ptr,sp,28
```

This is genuine matching difficulty: equivalent computations need not have
identical machine code. However, many later casts, pointer copies, and
initialization spellings reproduce already measured output.

The final reported `v61` residual still has population 4 and scheduling 8, with
incomplete allocation correspondence. Neither clean-C impossibility nor a
compiler-flag mismatch is established.

Evidence: lines 279–384, 462–726; checkpoint at line 732.

### E. Evidence interpretation and continuity records drift

In `DsSync`, the report explicitly prints:

```json
{
  "stage": "dbr",
  "agrees": false,
  "targetCount": 88,
  "candidateCount": 88,
  "differences": []
}
```

The agent treats equal counts and the empty differences list as “dbr agrees
fully,” despite the false agreement flag. It then pursues allocation while the
same report says instruction populations differ and value-web correspondence is
incomplete. Later measurements still show population differences of 15–17.

The presentation is confusing, but the downstream conclusion is not licensed by
it. Equal instruction counts are not agreement, and incomplete correspondence
must not be interpreted as an allocation-only residual.

A closure record also groups `v56`, `v58`, and `v59` as the same compiled words as
`v10`, although their printed measurement rows differ. Those rows do not support
whole-output identity. A similar local pattern or residual is not sufficient
proof that two complete candidates compile identically.

Evidence: lines 711, 919–945; variant measurements at 285, 672, 696, and 700.

### F. The agent repeatedly rediscovers translation-unit context

The project compiles ordered fragments as one production TU. The agent learns
this, then re-questions it and recreates declaration conflicts on subsequent
functions. Repeated detours concern:

- declarations already supplied by earlier fragments;
- aliases of section-relative storage;
- file/listing coordinates versus section offsets;
- compiler assembly macros versus expanded machine instructions.

Some manual comparisons initially use unexpanded candidate assembly against
expanded target instructions, creating spurious apparent differences.

This is both an agent-context problem and an opportunity to make preparation
packets and diagnostic interfaces less ambiguous.

### G. Controller behavior does not distinguish handoff from parking

After preserving the candidate and restoring the live stub, the agent requests
parking for the `DsQueueLen` blocker. The tool rejects the request:

> The active autoloop owns parking; report the blocker to it instead.

The agent reports the blocker, but the next controller message says no C has
been written and tells it to write the body. That conflates live integration
state with the existence of scratch candidates and measured evidence.

The agent then spends the remainder considering ways around the fragment
restriction, including hidden header definitions and bypassing normal compile
checks. No accepted bypass or verified completion appears in the log.

Separately, the `DsSync` phase contains eight aborted assistant responses within
approximately 30 seconds, interleaved with repeated continuation prompts. The
cause is not established by the log; repeated abort/retry cycles are runtime or
orchestration churn, not matching progress.

Evidence: lines 950–968, 1318–1348.

## Implementation workstreams

Most implementation belongs in `../psx-decompilation-harness`, not in this
project's function bodies. Preserve the original-byte oracle and existing
clean-source constraints throughout.

### 1. Repair delay-slot callback discovery and safe subdivision — P0

- Recognize a callback pointer completed in the delay slot of its consuming
  call, accounting for the call's link-register write and argument-use timing.
- Update both address-publication tracing and HI16/LO16 pairing validation.
- Retain independent-entry/control-flow requirements: a code address alone must
  not turn switch labels or interior blocks into functions.
- Extend the assembly backlog through the existing split mechanism so each
  discovered callback has its own function part.
- Leave callbacks as their existing extracted assembly until separately
  assigned; do not force their reconstruction into `DsQueueLen.c`.

Acceptance:

- All three callback entries are discovered from original relocations.
- `DsQueueLen`'s inferred extent is 16 bytes, not 448.
- The split preserves complete original code/data coverage and whole-member
  identity.
- A candidate containing only the simple `DsQueueLen` implementation can be
  measured and finalized with the callback parts retained separately.
- Negative tests cover interior labels, clobbers, ambiguous pairs, and invalid
  delay slots.

### 2. Make library diagnostic capabilities accurate — P1

- Exercise the actual native library candidate path in diagnostic integration
  tests, including object parsing, relocation handling, and provenance guards.
- Report unsupported target domains before invoking executable-specific code.
- Investigate `Native target changed` failures with source/output hash evidence;
  do not weaken the original-input immutability invariant.
- Allow deeper candidate-side diagnostics to consume explicit scratch sources
  without requiring premature live integration.

Acceptance:

- Each advertised diagnostic either produces valid library evidence or returns
  a precise capability refusal.
- Unsupported library requests do not search for a PS-X EXE.
- Rebuilding a candidate does not itself trigger an original-target mutation
  diagnosis.
- Tests cover explicit scratch candidates with a live `INCLUDE_ASM` stub.

### 3. Improve TU-aware preparation and declaration contracts — P1

- Reconcile SDK types and existing TU declarations without duplicating or
  inventing incompatible definitions.
- Resolve argument forwarding against original call-site and callee evidence;
  keep unresolved contracts explicit.
- Supply symbol/relocation-aware jump-table context to m2c where possible.
- Explain which declarations are already visible from earlier fragments, their
  ownership, and the designated destination for shared declarations.

Acceptance:

- Regression fixtures reproduce the six-argument `_DsPacket2` call correctly.
- Prepared fragments do not introduce the observed SDK/typedef collisions.
- Generation failures retain full diagnostics without presenting a stub build
  as candidate verification.

### 4. Make residual scope and pass ownership unambiguous — P1

- Label function versus whole-member counts and distinguish target extent,
  candidate extent, overlapping compared words, and omitted target words.
- Explain why an agreement flag is false when the displayed differences list is
  empty; absence of listed differences must not imply agreement.
- Keep incomplete value-web correspondence explicit in summaries and handoffs.
- Guide the solver by the earliest unresolved requirement; do not describe
  ungraded allocation as agreement or infer an allocation-only residual from
  equal counts.
- Provide comparable expanded original/candidate listings in one coordinate
  system, reducing ad hoc shell comparisons.

Acceptance:

- The `DsQueueLen` case cannot appear to be merely a one-word mismatch while
  omitting 108 target words without prominently reporting the omissions.
- The `DsSync` fixture does not imply dbr agreement from equal counts.
- Partial allocator evidence remains usable where justified, but is not
  promoted into proof that earlier residuals are settled.

### 5. Preserve trustworthy experiment memory — P1

- Bind claims of identical compiled output to the recorded output hash and
  comparison domain, including relevant compilation context.
- Distinguish identical output, equal residuals, and locally identical code.
- Check machine-verifiable assertions in closure records; retain bounded
  negative results with their source/context premises.
- Surface previously measured equivalent programs before another large
  spelling search, while preserving genuinely different variants.
- Carry a compact TU-context summary between function assignments so declaration
  and coordinate facts need not be rediscovered.

Acceptance:

- The reported `v10` / `v56` / `v58` / `v59` equivalence is checked against
  artifacts, not copied forward as unsupported prose.
- Changed context reopens a closure only within the scope its premises require.
- A later solver can identify the best preserved candidates and exhausted
  mechanisms without rereading the full session.

### 6. Allow escalation-aware agent parking — P0

Replace the blanket rejection of `psx_park_function` during an active autoloop
with an escalation-aware request handled atomically by the controller.

The agent must be able to report the blocker through the tool. The controller
remains responsible for deciding whether that request is an ordinary escalation
handoff or a durable park, using the authoritative configured ladder position.

| Campaign position | Result of an otherwise valid parking request |
| --- | --- |
| Earlier rung; another rung remains | Preserve candidate/evidence and hand off normally to the next rung. Do not park the function. |
| Final rung | Persist the park if its reason/evidence satisfies the existing parking policy; acknowledge it and advance the campaign. |
| Single-rung ladder | Treat as the final rung. |
| Position cannot be established | Do not infer final-tier eligibility. Return an explicit controller-state diagnostic and preserve the handoff; never silently park. |

Requirements:

- Use the actual attempt/tier position, not model name or the agent's claim that
  it is the final model. A ladder can repeat a model or use different roles.
- Being on the final rung is necessary, not sufficient: preserve the existing
  admissible reasons and evidence requirements. Matching difficulty alone must
  not be mislabeled as a witnessed build blocker.
- An earlier-tier request must not create a function-level parked record that
  causes later tiers or future worklist selection to skip it.
- Return a structured disposition such as `handed-off` or `parked`, including
  the current rung, next rung where applicable, reason, and evidence pointers.
- Persist scratch candidate paths, measurements, scoped closures, and source
  restoration state in the normal handoff. A restored live stub does not mean
  no C candidate exists.
- Consume the disposition in the controller. Do not follow an accepted handoff
  or park with generic “write the body” continuation prompts.
- Make requests idempotent: retries must not advance multiple rungs or create
  duplicate park records.
- Parking and escalation grant no source-policy exceptions, change no oracle,
  and do not authorize hiding other functions in headers or bypassing scope
  checks.
- Handle repeated aborted responses separately, with bounded retries/backoff
  and explicit runtime evidence rather than identical continuation spam.
- Outside an active campaign, retain the existing standalone parking workflow;
  there is no remaining campaign rung to escalate to.

Acceptance tests:

1. An earlier-tier agent requests parking for the witnessed `DsQueueLen` split
   blocker. The next tier receives the candidate and blocker evidence; no
   function-level park is written.
2. The final-tier agent makes a valid request for the same unresolved blocker.
   The function is durably parked and the campaign advances.
3. A single-tier campaign can park on a valid request.
4. Repeated requests and restarts neither skip a tier nor duplicate a park.
5. Invalid or unsupported blocker claims are returned with an actionable
   explanation; final-tier status does not bypass evidence requirements.
6. The controller distinguishes `live stub + measured scratch C` from `no
   candidate`, including when source was restored after a failed integration.
7. Unknown ladder position cannot accidentally park the function.
8. Abort/retry handling does not generate the observed rapid continuation loop.

### C2. Second witness: `libetc_3::SetIntrMask` (code address published from `.data`)

Recorded 2026-10-21 in an autoloop `/decompile` worker. Same structural class as
§C, different discovery route, so §1 must cover it too.

- The selected function is a 6-word accessor, `.text` 0x17C–0x194:
  `lui/lw %lo(D_00001898); lhu; jr $ra; sh $a0`.
- Its size-zero symbol is assigned an inferred extent of `0xF0` bytes
  (`build/libraries/disassembly/libetc_3/function-bounds.txt`:
  `SetIntrMask = 0x1fc; // type:func size:0xf0`), because the bound is taken
  from the next *named* symbol `func_000002EC` at 0x26C.
- The extra `0xD8` bytes (0x194–0x26C) are an independent entry, `T_00000214` in
  the listing: own frame (`addiu sp,sp,-0x18` … `addiu sp,sp,0x18`), ends in
  `jr $ra`, and starts after the accessor's `jr $ra` at 0x18C, so it cannot come
  from the accessor's source.
- It is published only as a code address from a data word. The original object's
  `.rel.data` holds 7 `R_MIPS_32` records; the one at `.data`+0x10CC references
  `.text` and its encoded addend is the raw word `0x00000194`. That word is the
  `D_00001870` handler-table slot at `.data`+0x10CC, and the public
  `ResetCallback` wrapper dispatches to it through `D_00001890->unkC`.
  `discoverPrivateFunctions` ignores non-code `R_MIPS_32` relocations entirely,
  so no entry is created and the fragment stays compound.
- Measured consequence: a candidate defining only `SetIntrMask` produces `.text`
  0x5F0 against the original 0x6C0 (exactly −0xD0 after section alignment, from the
  missing `0xD8` of code). Because a data reference's encoded operand is the
  symbol's **absolute LNK object address**, that shift moves the whole `.data`
  section and changes the encoded data address in *every* function of the member:
  `ResetCallback`'s `lw` at 0x4 encodes 0x1740 instead of 0x1810, `GetIntrMask`'s
  at 0x168 encodes 0x1748 instead of 0x1818, and `SetIntrMask`'s at 0x180 encodes
  0x1748 instead of 0x1818. Only 94 of 432 words then compare equal — those
  instructions that reference no data. The native comparator
  (`tools/lib/objectFormats/compare.ts`) compares raw words exactly and does not
  fold defined references, so this is one defect, not forty. Restoring the part's
  extraction returns 432/432.
- Both permitted source routes are refused, not merely unexplored:
  defining `T_00000214` beside `SetIntrMask` gives
  `SetIntrMask.c: must define only SetIntrMask`; listing both symbols in
  `src/libraries/libetc/3-intr/tu.json` gives
  `A folded module is its TU's only part` (the member has 14 parts, and the
  module form would require reconstructing the whole member).
- No project-side workaround exists: the symbol-bearing ELF view
  (`library-input/redux/libetc/3-intr.o`) is a generated, gitignored conversion
  artifact, and `library-input/` is outside `autoloop.integration.allowedRoots`.

Acceptance for the §1 fix, in addition to the existing list:

- A code address published by a non-code `R_MIPS_32` relocation (`.data` word →
  `.text` + encoded addend) is discovered only when the target is an
  independently enterable entry that exits without falling through
  (`independentAddressEntry`), never on a switch label or interior block.
- After re-split, `SetIntrMask`'s extent is `0x18` bytes, `T_00000214` becomes its
  own part held as extracted assembly, and `SetIntrMask.c` defining only the
  accessor reaches `MATCH` for the whole member.

**The interior entry is ordinary clean C, not hand-written assembly.** A
build-only two-function TU (harness `compileSource` with explicit
`preprocessedText`, so the single-symbol part gate is not consulted; the pristine
native original remains the oracle) reconstructs it in eleven measured steps to
**58/60 words, whole member 430/432**. The candidate is preserved at
`build/exp/SetIntrMask_interior_58of60.c`. Findings worth keeping:

- The hardware-register pointers behave as `volatile u16 *` (that is what makes
  the mask read-back reload instead of forwarding the stored zero); the
  neighbour `GetIntrMask.c` must then declare the same type, a shared-declaration
  change.
- The `a0` base of the `D_00001890->unk4` store is the argument of the following
  call: the original passes the table to `_96_remove`
  (`_96_remove(D_00001890);`), which is why the store lands in that call's delay
  slot through `a0` instead of a reused `v1`. This single fact moved the result
  from 427/432 to 430/432.
- The whole accessor and the first 52 of the interior body's 54 words are then
  identical; the last two are a post-RTL register tie-break. The `.rtl` dump is
  already the target's shape — `(set p (plus p -60))` followed by a separate
  `(set v0 p)` copy, both in the target's order — and the scheduler/allocator
  coalesces that copy into the addiu (`addiu v0,s0,-60`) instead of keeping the
  variable update and copying (`addiu s0,s0,-60; move v0,s0`). Five spellings of
  the same tail (compound/simple assignment, assignment-expression, comma
  expression, separate temporary, `register`) compile to identical output, so
  the axis is exhausted for source shapes; the allocator tools are unavailable
  while the part cannot be compiled in its TU. This is allocation-axis work,
  not a semantic difference.

## Non-goals and verification boundaries

- Do not solve `_DsPacket2` or `DsSync` by changing flags, original inputs,
  symbol meanings, or policy constraints to fit an existing candidate.
- Do not treat failed spelling searches as proofs of impossibility.
- Do not count a scratch byte match as completion: successful integration and
  `psx_finalize_function` remain required.
- Preserve original input integrity and whole-member identity while repairing
  discovery and diagnostic interpretation.
- This plan makes no changes to live function sources or campaign state.
