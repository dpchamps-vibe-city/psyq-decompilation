# REALLOC3: a one-trip loop boundary changes CSE

## Verified result (2026-10-17)

`libapi_87::realloc3` is recovered in
`src/libraries/libapi/87-realloc3/realloc3.c`: **57/57 words exact**.
`psx_finalize_function` passed exact diff, full build, scope and clean-source
checks. Documentation handoff identity:
`2b232023496cad13043cd7ae57fb0a22ce4c3e0d4b7626e5cb9c554a41ad7230`.
Verified source SHA-256:
`a91fb06f4e53c73f0fb1cabf0e40527c95801cda42bb3d6e2eb8373e62a70071`.

The owning-member receipt is
`build/libraries/verified/libapi_87.json`, whole-member **108/108**,
identity `9ec5b129043bf4154a5d6c30e6b17e0e14357b791936ccd156209f40fd326676`.
At this verification the rollback helper was C and the byte-copy helper was
still assembly-backed. A whole-member match does not mean all its functions
were reconstructed. Receipt and documentation identities are different domains.

Compiler and configuration were unchanged during this repair: GCC 2.7.2 with
the existing owning-TU override
`-fforce-addr -fno-rerun-cse-after-loop`. No additional override, inline assembly,
register pinning or policy exception was introduced. This is a byte-verified
reconstruction, not proof of Sony's historical spelling or command line.

## Operation

A null pointer delegates to `malloc3`; zero size frees a nonnull pointer and
returns null. Otherwise round the payload to eight-byte units, including its
header. Equal size returns the original pointer. Shrinking splits and frees a
tail block. Growing frees the old block and attempts an allocation; failure
restores the free-list snapshots through `func_0000014C`. Success copies the
old payload through `func_000001A0` and returns the allocation.

The signed block-count comparison is preserved. `malloc.h` supplies the public
allocator declarations; `free3` takes only its payload pointer. Values left in
`$a1` and `$a2` at a call are not evidence for additional parameters.

## The successful distinction

The important boundary is between forming a header pointer and reading its
field. The exact source uses:

```c
rounded_units = (size + 7) >> 3;
do {
    bp = (Block *)((u8 *)ptr - 8);
} while (0);
old_units = bp->size;
new_units = rounded_units + 1;
```

This executes once, with no added machine branch. It is not interchangeable
compiler input with an ordinary compound block in this vintage compiler.

The ordinary source's first CSE pass changes the header load to `ptr - 4`.
The target instead retains `bp = ptr - 8`, followed by a load at `bp + 4`.
Native evidence:

- `build/realloc3-reopened/flag-experiment/current/candidate.i.cse` has
  UID 48 defining pseudo 74 as `pseudo72 - 8`, but UID 53 loads through
  `pseudo72 - 4` rather than pseudo 74.
- The integrated source's dumps under
  `build/loopTrace/libapi_87::realloc3/` retain
  `NOTE_INSN_LOOP_END` UID 65 between the header definition and UID 71's load
  through `pseudo74 + 4`. These scratch artifacts can be overwritten; check
  their source provenance before reusing them.
- `gcc/cse.c`, `find_best_addr`, folds non-register address expressions.
  `cse_end_of_basic_block` explicitly stops at `NOTE_INSN_LOOP_END` before
  loop optimization; the associated continuation logic is in
  `cse_basic_block`. The one-trip source boundary therefore changes the CSE
  region even though there is no runtime loop in the final code.

The existing no-second-CSE override is part of this experiment's premise.
This result does not prove the same spelling is exact with baseline flags.

### Scheduling and web shape still matter

Putting the complete `((size + 7) >> 3) + 1` expression before the one-trip
block fixes address population but leaves a block-4 scheduling residual.
Leaving the final `+ 1` after the field load fixes scheduling. Reusing
`new_units` for both stages then leaves an allocation difference; a separate
`rounded_units` temporary removes it.

Measurements under
`build/pipelineReversal/libapi_87::realloc3/objective/`:

| Source under `build/realloc3-reopened/` | Measurement | Result |
| --- | --- | --- |
| `ordinary.c` | `measurement-uT0RkQ` | `[0,8,0,1]`; folded header offsets |
| `header-before-guard.c` | `measurement-ltbf0U` | Identical compiled output to ordinary source |
| `header-once.c` | `measurement-zwnrLU/v1` | Population reduced to 4; web correspondence incomplete |
| `round-then-header-once.c` | `measurement-YTEovx` | `[0,0,1,0]`; scheduling only |
| `round-split-header-once.c` | `measurement-wGKZSh` | `[0,0,0,1]`; allocation only |
| `rounded-web.c` | `measurement-qzZMS9` | **EXACT, 57/57** |
| Integrated source, SDK declarations and comment | `measurement-yXzq4h` | **EXACT, 57/57**, followed by full finalization |

Keys are control-flow/population/schedule/allocation, not byte distances.
An incomplete correspondence is not allocation agreement. The intermediate
source names and measurements, not word-count improvement, establish this
sequence of source distinctions.

## Why the prior park was not an impossibility result

Saved session:
`/home/dave/.pi/agent/sessions/--home-dave-Documents-code-psyq-decomp--/2026-10-17T00-25-20-310Z_01a1473f-b6b6-765a-9b1f-7fb790e8eb71.jsonl`.

The ledger at reopening held 50 measurements and 23 distinct compiled outputs;
27 were repeat spellings of already measured programs. The earlier closure
explicitly concerned pointer/offset spellings and a different flag context,
`-fno-cse-follow-jumps -fno-cse-skip-blocks`. It did not exclude all clean C.

The approval note recorded those flags as forbidden when `realloc3` was
parked. Later matching of the same member's rollback helper changed the owner
configuration to the currently authorized pair. The old policy finding is
historical, not a current blocker. Reopening required a fresh measurement of
ordinary C under the actual owner flags, not resuming its old score as if the
compiler context were unchanged.

The decisive extra source axis was a syntactic CSE-region boundary, not another
cast spelling or a new flag. An earlier claim that do/while spellings did not
help was scoped to those particular sources; it did not establish that placing
this specific definition immediately before a loop-end note was ineffective.

## Harness observations to revisit after both repairs

- The reversal correctly exposed header-offset population differences, but its
  generic statement that differing populations mean differing source semantics
  is too strong here: the semantic operation is unchanged; CSE representation
  and region boundaries differ.
- The inventory similarly called the `+4` versus `-4` effective-address change
  a semantic defect. Such an offset multiset is a useful signal, not a proof
  without base provenance.
- Existing native-dump evidence already shows zero-width loop notes influencing
  delay-slot filling and allocation in the allocator neighbors. CSE-region
  partitioning needs the same explicit treatment; searches over executable CFG
  shapes alone miss it.
- The flag probe reported `inconclusive` and warned that only its selected
  source had been tested. That warning was correct. Manual counterfactuals in
  `build/realloc3-reopened/flag-experiment/` did not justify another override.
- `callee_truth` still printed an undeclared callee named `.text`, reflecting
  local section-relative call representation rather than a real C declaration
  to invent. Public allocator declarations were corroborated.

No new original-TU membership evidence was needed or produced. REALLOC3.OBJ's
three-function membership and snapshot dependencies were already recorded in
`notes/file-groupings.md`; the grouping ledger is unchanged by this repair.
The old park note is historical and does not supersede this verified result.
