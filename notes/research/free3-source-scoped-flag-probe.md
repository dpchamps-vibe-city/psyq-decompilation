# FREE3: probe the source–flag pair, not a workaround in isolation

## Verified result (2026-10-16)

`lib_5a59d0efe7ad3e69_0::free3`, in
`src/libraries/libapi/86-free3/free3.c`, matches **84/84 words** of its original
member. `psx_finalize_function` passed exact diff, full configured build, scope,
and clean-source gates. No compiler replacement, register pinning, or new
assembly was needed. One evidence-backed **owning-TU flag override** was needed
for this reconstruction:

```make
CC1FLAGS_lib_5a59d0efe7ad3e69_0 := -fno-rerun-cse-after-loop
```

The compiler remains configured GCC 2.7.2, with the remaining production flags
and GAS assembler unchanged. This is a verified reconstruction configuration,
**not proof of Sony's historical command line or original source spelling**.
Nor does it prove that every possible baseline-flags C program must fail.
Do not extend this override to adjacent allocator objects without measuring them.

Verification identities:

- Documentation handoff: `0b1745f68a27ef5cfd6378bcf9ac809ae0f3cf6e3202302a1059f35aa2c45b3e`.
- Whole-member receipt: `build/libraries/verified/lib_5a59d0efe7ad3e69_0.json`,
  identity `9e1d4f4209b08f17a4e6f30e2dfd0b4c7f6dfc91f8c7b9f50e58d6596e49fbf5`.
- Verified source SHA-256:
  `0c77f2662f879b3794eb643311fde9520e0a7750ee6257f486384ab99340fbed`.
- Original: `library-input/redux/libapi/86-free3.o`, SHA-256
  `14f59ff2225bb74bfade9fd38ffa814072bac6eb65d8bdb74b6eeba202b8ba86`.

These identities describe different evidence domains; they are not interchangeable.
The 84-word owning-member result includes trailing padding, whereas the flag
probe reports an 82-instruction target stream.

## What the function does

For a nonnull payload, locate its eight-byte block header, find the insertion
point in an address-ordered circular free list, save the two affected blocks and
old `_freep` for rollback, merge adjacent blocks when applicable, and publish the
new free-list cursor. `_r_bp` and `_r_p` have pointer/link/size fields at offsets
0/4/8. The upper merge also checks that the neighboring block's size is nonzero.

The final source uses the ordinary free-list search and direct snapshot field
assignments. It does **not** assign snapshot-address pointers in every loop exit
or reuse the payload argument as a snapshot pointer.

## The two distinctions that settled it

### 1. Preserve the snapshot bases by changing the measured CSE configuration

The original has one HI16/LO16 address pair for each of `_r_bp` and `_r_p`, then
stores through that register at offsets 0, 8, and 4. The baseline compilation of
straightforward C folds the nonzero field addresses back into separate symbolic
memory operands. That is an address-population difference, not initially a
scheduler tie.

The native before/after comparison preserved in
`build/free3-repair/cse2-diff.txt` shows the second CSE pass replacing forms such
as:

```text
mem(reg_snapshot_base + 8)
    -> mem(const(symbol_ref("_r_bp") + 8))
```

The same transformation occurs for offsets 4 and 8 of both snapshots. Disabling
that second CSE pass retains the shared bases; production scheduling and
allocation then produce the target snapshot block without pointer workarounds.
This diff was captured from `canonical.c`, the version with the header
calculation before the guard; it establishes that candidate's address rewrite,
not unavailable original RTL.

The automatic flag detector did **not** nominate this fingerprint: its report
remained `inconclusive`, and its absolute `_freep` load-pair observations are
explicitly ordinary assembler expansion. The override's justification instead
combines the original snapshot-base reuse, the native CSE rewrite, the dominant
source-scoped flag column, and a whole-member exact result with no contrary
region. Do not cite the detector as having independently identified the
historical flag.

### 2. Calculate the header after the null guard

Keep this source order:

```c
if (arg0 == 0) {
    return;
}
p = (Block *)((u8 *)arg0 - 8);
```

Moving the calculation before the guard looks attractive because the target
executes it in the guard's delay slot. It is nevertheless a different compiler
experiment. With the successful flag delta, the before-guard source leaves one
word wrong at `.text+0x40`:

```text
target:    sltu v0,a1,a2
candidate: sltu v0,v1,a2
```

Both follow `move a1,v1` and compute the same comparison. For the preserved
before-guard candidate, `.jump2` still compares `$a1`; `.dbr` changes it to `$v1`.
For the after-guard candidate, `.dbr` retains `$a1` and fills the entry delay slot
with the header calculation. `reorg.c`'s `fill_slots_from_thread` contains the
register-copy substitution rule. The dumps establish the changed pass and
operands; they do not by themselves explain every earlier traversal decision.
Do not try to fix this one-word difference through register allocation.

### Measured contrasts

Scratch sources and counterfactuals are under `build/free3-repair/`:

| Source/configuration | Observed result |
| --- | --- |
| `p-after.c`, baseline production flags | Flag-probe masked alignment 17/82; not exact. |
| `p-after.c`, add `-fno-rerun-cse-after-loop` | Flag-probe masked alignment 82/82; separately confirmed zero differences across all 336 `.text` bytes and whole-member MATCH. |
| `canonical.c`, same single flag delta | One `.text` word differs, at `+0x40`; header calculation precedes the guard. |
| Either source, also add `-fno-thread-jumps` or `-fno-expensive-optimizations` | No improvement over its single-delta result; neither extra option was adopted. |
| Either source, also add `-fno-cse-skip-blocks` | 71 `.text` words differ; this is not a substitute for the measured configuration. |
| Integrated source with the single owner override | `measurement-88VWfq`: EXACT, 84/84; full finalization subsequently passed. |

The counterfactual script, complete argv, preprocessed sources, assembly,
objects, native dumps, and raw section comparisons are preserved in
`build/free3-repair/flag-counterfactual.py` and
`build/free3-repair/flag-counterfactual/`. Its raw section comparison was an
intermediate check, **not** a replacement for the later owning-TU oracle and
full finalization gate. `build/flagProbe/lib_5a59d0efe7ad3e69_0::free3/report.json`
at documentation time describes `p-after.c`; these scratch reports can be
overwritten, so check their source hashes.

## Why the saved agent session did not finish

Primary record:
`/home/dave/.pi/agent/sessions/--home-dave-Documents-code-psyq-decomp--/2026-10-16T21-34-53-337Z_01a146a3-a999-723d-9010-6da9f19b0340.jsonl`.
It ends at `2026-10-16T22:14:25.729Z` with another candidate inspection, not a
successful finalization. The observations below concern recorded actions, not
an inferred motive or a claimed terminal blocker.

### The flag hypothesis was tested on the workaround, not the ordinary source

The session's sole `psx_flag_probe` call, entry `fabfbbf1` at 21:59:53, selected
`build/free3/v_h5.c`. Result `e8d43152` reported:

- baseline: 17/82 masked, 83 instructions;
- `-fno-rerun-cse-after-loop`: 9/82 masked, 84 instructions;
- conclusion: **inconclusive**.

That candidate already used altered snapshot-pointer birth/control structure.
The result says what that source does under those flags. It does not close the
same flag applied to the ordinary direct-field source. The report explicitly
warned that only the selected source was scored and recommended probing other
mechanically plausible source shapes.

The decisive correction was to measure the **source–flag interaction**. The
ordinary source was poor under the baseline, and the flag delta was poor on the
workaround; the ordinary source **with** the delta is exact. Keeping only the
best baseline-scored source can delete the configuration's winning candidate.

### Scheduler work explained a self-created residual

The agent found ways to retain snapshot bases by assigning their addresses in
several loop-exit arms. Later variants reused `arg0` for `_r_bp` and reached
allocation agreement while leaving three scheduling differences around `_r_p`.
That was real evidence about those variants, but not evidence that the original
programmer used the same multiple-set pointer webs.

The session repeatedly returned to whether `_r_p` needed a single-set birth,
a different live range, or reordered stores. At reopening, the ledger reported
85 measurements, 55 distinct compiled outputs, and 30 respellings. This is a
ledger count, not a census of every standalone compile in the session. Several
families compiled identically. The repair's aggregate-copy and loop-spelling
probes also failed to settle it; the eventual cause was not a cleverer spelling
of the retained pointer workaround.

**Lesson:** a late-pass near match does not validate the source assumptions
that manufactured its webs. Retain the simple source as a separate branch and
retest upstream configuration against it.

### A separate COMMON-symbol defect remained

The attempted C also tentatively defined `_r_bp`, `_r_p`, and `_r_freep`, although
`_data.c` already included their original COMMON declarations. The target's
12-byte `_r_bp` and `_r_p` have COMMON alignment **8**. The duplicate compiler
`.comm symbol,12` directives caused GAS to give them alignment **16**.

This is independently observable with `readelf -s`: COMMON symbol `Value` is
alignment, not an address. The reopened baseline object in
`measurement-Pj2B9i/baseline/candidate/` has `Value=0x10` for these two symbols;
the original has `Value=0x8`. The final header declares them `extern`, leaving
storage to the existing original-data fragment. No data fragment was rewritten.
Matching instructions alone would not have fixed this owning-member defect.

### Diagnostic failures were capability limits, not exhausted source domains

The session did try deeper tools, but several could not perform their advertised
search on this target/toolchain:

- Recipe/near-miss tools refused relocatable-library targets. The same refusal
  was retried later, including entry `f6c0309f`.
- Source-shape searches failed on a missing `.i.regmove` artifact; see
  `ba21ddc6` and `4208032e`.
- Local-allocation instrumentation reported a missing `alloc_qty` anchor;
  `8a62ba1f` and the later solver attempt did not establish an allocation UNSAT.
- Some analyses selected the live assembly stub rather than a parked C candidate
  and therefore had no function RTL to analyze.

These failures reduced available assistance. They did not show that clean C
was impossible, that a bounded grammar had been exhausted, or that a compiler
replacement was required. Do not retry an unsupported route without changing
its documented blocking premise.

## Checklist for the next similar case

1. Keep an ordinary semantic reconstruction alongside target-shaped variants.
   Probe flags early on **both**, not just on the current baseline-score winner.
2. State every negative result with its source, flags, context, and actual tool
   coverage. `inconclusive`, unsupported, and missing-artifact failures close no
   compiler-state domain.
3. For repeated global-field accesses, inspect original relocation reuse and the
   native CSE before/after form before treating base placement as scheduling.
   A source's CSE workaround can itself create the allocation problem.
4. Preserve source statement placement relative to guards as an experimental
   axis. A final delay-slot instruction need not have been written before the
   branch. Use `.jump2`/`.dbr` to distinguish copying from allocation.
5. In library mode, validate COMMON size/alignment and ownership as well as code
   and symbolic relocations. Do not duplicate assembly-backed storage in C.
6. Library overrides are keyed by **member ID**, not the function basename. The
   flag-override policy authorization must also cover that owner key. Here the
   initial function-qualified authorization did not cover the added
   `CC1FLAGS_lib_5a59d0efe7ad3e69_0` line; the correctly scoped owner authorization
   passed the existing gate. Keep the directly preceding evidence comment.
7. Promote only after whole-member and full finalization gates pass. A masked
   shape hit or a manual `.text` match is not completion.

No new original-TU membership evidence was produced. The heap3 COMMON/global
cluster and FREE3.OBJ's separate ownership were already recorded under
I_HEAP3.OBJ in `notes/file-groupings.md`; that ledger is unchanged. This case
study records matching technique and the saved-session retrospective only.
