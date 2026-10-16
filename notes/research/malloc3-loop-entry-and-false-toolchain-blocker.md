# MALLOC3: loop-entry state, not an impossible compiler

## Verified result (2026-10-16)

`lib_55fbf6eed978186c_0::malloc3`, in
`src/libraries/libapi/85-malloc3/malloc3.c`, is **44/44 words exact**.
`psx_finalize_function` passed exact diff, full configured build, scope and
clean-source gates. Documentation handoff identity:
`8b7cf1e6b1081788957b7399bc068044159b4d80ac97af714461fa705ec8d7cc`.
The owning-member receipt is
`build/libraries/verified/lib_55fbf6eed978186c_0.json` (whole-member match,
including symbolic relocations), identity
`87b0b44353eaba7543aab82ab333e333f1dca42b7f543950563ec03f35428dfe`.
These are different identity domains, not interchangeable hashes.

The configured GCC 2.7.2 compiler, production flags and assembler are unchanged.
No assembly, register pinning, flag override or policy exception was needed.
Verified source SHA-256:
`b2b64f59cd3c3bb5ccfaba050d5d5a614c1940a55cc3738bdbb334a368974dd3`.

The function rounds a nonzero request to eight-byte alignment, searches the
circular free list, removes an exact-fit block or splits space from a larger
block's tail, and returns the payload. Exhaustion or an initially zero request
returns null.

## The successful source distinction

The parked draft used an early null return followed by
`while (size & 7) size++;`. The verified version carries the first mask value
across the zero-size guard and jumps into the **test of a syntactic do loop**:

```c
alignment = size & 7;
if (size == 0) {
    goto no_memory;
}
goto alignment_test;
do {
    size++;
    alignment = size & 7;
alignment_test:
    ;
} while (alignment != 0);
```

Both failure paths share `no_memory: return 0;` in the verified complete source.
The first trip tests the original size without incrementing it. Later trips
increment and recompute the mask. Computing the first mask before the guard has
no memory effect and does not change the zero-request result.

This is an oracle-verified reconstruction, **not proof that Sony used this
historical spelling**. Preserve the distinction between normal loop entry,
plain labels/backward goto, and entry into a syntactic loop when comparing
compiler input.

### Measured contrasts

All paths below are under `build/malloc3-reopened/` and use production settings.
The measurements are under
`build/pipelineReversal/lib_55fbf6eed978186c_0::malloc3/objective/`.

| Source / measurement | Observed result |
| --- | --- |
| `baseline.c` / `measurement-3PRqTz/baseline` | Parked draft; staged key `[0,1,0,0]`. Entry delay slot contains `move v0,zero`, not the initial mask. |
| `alignment-web.c` / `measurement-3PRqTz/v1` | Carries the mask across the guard but uses an ordinary `while`; entry mask appears, but an additional initial loop guard remains. Not exact. |
| `alignment-labels-shared.c` / `measurement-2EO0Pk/v1` | Plain labels/backward goto, same mask initialization and failure join as the winner. Entry is right, but loop delay slot contains `addiu v0,a0,7`; no compensating decrement. Not exact. |
| `alignment-do-entry.c` / `measurement-hVz0uA/v1` | Replace that label/backward-goto loop with the externally entered `do` above. **44/44, whole-TU MATCH.** |
| Live source / `measurement-kSXg2Z/baseline` | Integrated source reconfirmed **44/44, whole-TU MATCH**, then passed finalization. |

The plain-goto-to-do comparison isolates the syntactic-loop distinction. The
whole baseline-to-winner change is broader; it does not independently prove
that every other statement or failure-join spelling is necessary.

## What the native dumps actually establish

The exact candidate's dumps are in
`build/loopTrace/lib_55fbf6eed978186c_0::malloc3/`. At documentation time they
correspond to `alignment-do-entry.c`, which differs from the live source only
in whitespace. These scratch dumps can be overwritten; check provenance before
reusing them.

1. `.i.loop` prints **“Loop at 24 ignored due to multiple entry points.”**
   Refusing loop optimization does not erase the syntactic loop notes.
2. `.i.jump2` retains UID 10 (`v0 = a0 & 7`) **before** entry branch UID 13.
   UID 21 jumps to label 35, the alignment test. UID 29 increments `a0`,
   UID 31 recomputes the mask, and UID 37 branches back to label 25. A
   `NOTE_INSN_LOOP_BEG` immediately precedes that loop-header label.
3. `.i.dbr` puts UID 10 in entry branch UID 13's delay slot. This is a
   backward-moved instruction already present before the branch, **not a
   requirement to steal it from the branch's fallthrough thread**.
4. The same `.i.dbr` puts increment UID 29 in loop branch UID 37's delay slot,
   redirects the back edge to the mask computation, and adds UID 169,
   `a0 = a0 - 1`, on exit. There is no explicit compensating decrement in C.
   The initial unconditional jump remains unfilled; the assembler supplies
   its nop.

The deciding rules are readable in
`tools/vendor/gcc/2.7.2-psx/src/gcc/reorg.c`:

- `fill_simple_delay_slots` (around line 2798) scans backward for a safe slot
  instruction. This supplies the entry mask in the exact program.
- `mostly_true_jump` (around line 1335) returns **2** for a branch whose target
  follows `NOTE_INSN_LOOP_BEG`; an otherwise unclassified `NE` test gets **1**.
- `fill_eager_delay_slots` (around line 3632) passes `prediction == 2` as the
  `likely` argument to `fill_slots_from_thread`.
- `fill_slots_from_thread` (around line 3256) has the compensating-arithmetic
  path guarded by `delay_list == 0 && likely`: move the target increment into
  the slot and emit its inverse after the branch.

This explains the observed plain-goto/do difference: retained loop notes make
that compensation route available even though loop.c refused to optimize the
multiple-entry loop. See the independently solved
[REALLOC2 case study](realloc2-private-resize-control-shape.md) for another
same-toolchain example where those notes survive a multiple-entry refusal and
affect a later pass. That is a technique relationship, not same-TU evidence.

## Why the previous agent stopped incorrectly

Primary record:
`/home/dave/.pi/agent/sessions/--home-dave-Documents-code-psyq-decomp--/2026-10-16T20-07-01-275Z_01a14653-379b-7428-b9cf-86e6e19365af.jsonl`.
The following diagnoses concern observable experiments and claims, not inferred
model intent.

### 1. A bounded spelling search became an unbounded impossibility claim

The `manual-cc1-sweep` closure and final report asserted that the configured
compiler could not produce the target “for any source.” At reopening, the
ledger contained **49 measurements, 13 distinct compiled outputs and 36
respellings**; those counts are not 36 distinct compiler programs. In particular,
changing `while` to `for`, `% 8` to `& 7`, or `size++` to `++size` often produced
the same words.

Those measurements closed their measured spellings, not the externally entered
syntactic-loop construction. The new exact result with the unchanged compiler
is a direct counterexample to the universal claim. Do not treat the old closure
as a live blocker. Its omitted premise was the source/loop-entry family being
tested, not merely compiler version and flags.

### 2. Differential compilation was overinterpreted

The other Sony compiler builds emitted the desired entry block for the same
preprocessed draft, but differed elsewhere and did not match the whole member.
That demonstrates compiler sensitivity **for that input**. It neither identifies
the historical compiler of this object nor proves that another input cannot
match under the configured compiler. The old conclusion “toolchain blocker,
not a source defect” was not licensed by this experiment.

The decisive source lever was upstream of delay filling: supply a mask before
the guard and preserve loop-entry notes. Explaining what reorg did to the
parked RTL was not a proof that all C must produce that RTL.

### 3. Some purported variant measurements measured only the live baseline

Session entries `2a4152ef`, `8d449807` and `e2bd1398` call
`psx_residual_objective` with **`src`**, naming `malloc3_v_g.c`, `ZZ.c` and
`ZY.c`. That tool accepts **`source: [path]`**, unlike several other diagnostics
which accept `src`. Each corresponding result lists only the live source and
its provenance, with no `v1` row for the requested file.

These calls cannot count as tests of those variants. This does not establish
that any of them would have matched; it establishes a measurement-attribution
error. Always confirm the candidate path/hash and variant row in the result,
not just that a tool returned a residual.

### 4. A provisional normalized residual was stronger-sounding than its evidence

The reverse-pipeline report in session entry `e9a9d6d8` says the pre-delay-slot
round trip is unavailable and labels its owner reconstruction provisional.
Nevertheless, its generated explanation says the population differs and “the
source semantics differ.” Here the parked and exact programs implement the
same alignment operation, while delay filling changes duplication and placement
of the mask instruction. Do not turn that normalized population label into a
proof of a semantic defect or a compiler impossibility. The native `.jump2` /
`.dbr` comparison is the discriminating evidence.

### 5. Escalation exhaustion was not a witnessed build blocker

Both explicit `psx_park_function` calls were refused because the active autoloop
owned parking. The controller subsequently recorded **`escalation-exhausted`**
at `2026-10-16T20:56:49.720Z`, with no policy findings. That is the observed
worklist outcome; it is not evidence that compiler replacement or human policy
approval was required. The function was unparked and finalized in this repair.

## Guidance for the next similar residual

- Before repeating an experiment, inspect output hashes and the actual source
  provenance. Different filenames and successful tool invocations are not
  evidence of distinct measured programs.
- For a residual at loop entry, vary **where the first value is born** and
  **whether syntactic loop notes survive**, not just operator spelling.
  Compare ordinary entry, plain goto, and external entry into `do` as separate
  complete-source hypotheses. None is a universal replacement for the others.
- An optimizer refusing a loop does not make its loop notes irrelevant to
  later branch prediction, delay slots or allocation.
- Read native before/after dumps when inverse-pass ownership is provisional.
  A final slot occupant does not uniquely identify where that instruction
  existed before reorg.
- Keep a candidate that fixes the target region even if another region or a
  block-indexed residual looks worse; inspect its actual instructions before
  discarding the newly reached mechanism.
- Phrase a negative result as “no candidate in this measured grammar, with
  these inputs,” never “no source can match.” Compiler comparisons do not
  remove that qualification.
- Promote only after the whole-member oracle and full finalization gate pass.
  The current source, not the old parked draft, is the verified starting point.

No new original-TU membership evidence was produced. `_freep`'s heap3 cluster and
member boundaries were already recorded; `notes/file-groupings.md` is unchanged.

## Reproduction identities and stale-record warning

Original member: `library-input/redux/libapi/85-malloc3.o`, SHA-256
`00a3b77463e2e7978591be0c5fcd6a8bc9bb3c7b12240219f6cb47711941cf14`.
TU manifest: `src/libraries/libapi/85-malloc3/tu.json`.
Original listing:
`build/libraries/nonmatchings/lib_55fbf6eed978186c_0/malloc3.s`.
Ledger: `build/experimentLedger/lib_55fbf6eed978186c_0::malloc3.jsonl`.

The old `manual-cc1-sweep`, `sdk-cc1-comparison` and
`differential-cc1-compile` records remain historical measurements. Their
all-source impossibility / historical-compiler interpretations are superseded
by the exact counterexample above. This documentation phase edits only notes,
so it does not rewrite those build-local records. The resolved approval note
links here to prevent the old park from being mistaken for current work.
