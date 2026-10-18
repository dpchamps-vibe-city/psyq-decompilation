# QSORT: local byte pointer and partition-pointer birth

## Verified result

- Target: `libc_52::qsort`, LIBC's `52-qsort.o`.
- Source: `src/libraries/libc/52-qsort/qsort.c`.
- Owned header: `include/library/52-qsort.h`. It includes the reference
  `qsort.h` and declares the member's private byte-swap helper.
- `psx_finalize_function` passed exact diff, full configured build, scope and
  clean-source gates on 2026-10-17. Supplied source/evidence identity:
  `06c74028d9e708ea24445834dd0cd4aeb28c97e71f18a8184b960a984f8c2b00`.
- Whole-member receipt: `build/libraries/verified/libc_52.json`,
  `MATCH`, **100/100 words**, no section/symbol/relocation differences.
  Its separate whole-member identity is
  `f37ea2723a1baf7b008ba556c2e238f2eed44ea7f6b103b048e70fac4e6e3698`.
- Original object SHA-256:
  `82d016933ade74138ab823bf269f7c42e18e56c42faeec3bd0e776f912169e6e`.
- Source SHA-256:
  `1cfe235b2502b8203a1f6faab7a95e401518ea9464ac3c088618fbe74c51309f`.
- Owned-header SHA-256:
  `4faf79be47dd32dce19faa8c48134aeb86fa03923fd4ebbd7389919acd4a01de`.

The private helper fragment `func_000001B8.c` remains assembly-backed and
unchanged. Whole-member identity does not mean every function in the member
has been reconstructed in C. LIBC2's separate `13-qsort` was not changed.

## Behavior and declarations

This is in-place recursive quicksort over fixed-size records. Counts below two
return without a comparison. The two-record case compares the first and second
records and swaps only when out of order. For larger inputs, the middle record
is swapped into the first position as pivot; records strictly below it are
partitioned toward the beginning. After placing the pivot, the two remaining
ranges are sorted recursively. Redundant self-swaps are skipped.

The reference `library-input/converted/include/qsort.h` declares the public
entry as `void qsort(void *, size_t, size_t, int (*)())`, with `size_t` an
unsigned int. The source preserves that compatible signature and the vintage
unprototyped comparator type. Both comparator call sites pass **two** record
pointers. The m2c draft omitted the first argument in the two-record case:
there, original `$a0` still holds the incoming base at `jalr`; absence of a new
argument-setup instruction is not absence of the argument.

The private helper takes two buffer pointers and an unsigned byte count. Its
original code exchanges bytes with `lbu`/`sb`, indexing from zero to the count.
Only its declaration was added; its implementation was not part of this task.

## Two source changes that closed the residual

These are measured constructions under the configured `trunk-19970318` GCC,
production `-O2 -G0` flags and GNU assembler path, not proof of the historical
source text. No compiler flags, assembly workarounds or policy exceptions were
introduced. All investigation used local evidence.

### 1. Keep the public base separate from the local byte pointer

The earlier candidate used the first parameter itself as the persistent byte
pointer. Introduce the ordinary local view instead:

```c
void qsort(void *base, unsigned int count, unsigned int size, int (*compare)()) {
    unsigned char *first;
    /* Other declarations. */
    first = base;
    /* Scan and partition through byte pointers. */
}
```

This moved the persistent-base copy to the required position after the other
argument copies in the entry block. The staged residual changed from
`[cfg 0, pop 0, sched 2, alloc 2]` to `[0, 0, 0, 2]`. Merely changing the
parameter from an integer to a byte pointer had previously reproduced the same
compiled output, so pointer type alone was not the decisive change.

### 2. Initialize the partition pointer after the pivot swap

The near-match initialized `partition = first` before calling the byte-swap
helper. Its native scheduled RTL then used the partition pseudo for both base
arguments of that call. The trace assigned that pseudo `$s0` and the loop index
`$s1`, opposite the target. The trace's `.greg` allocation order establishes
that these were global allocations, despite the residual report's provisional
local-allocation label.

Move the assignment after the pivot swap:

```c
func_000001B8(first, first + (count >> 1) * size, size);
partition = first;
for (i = 1; i < count; i++) {
    /* Partition records. */
}
```

This avoids offering the partition copy to CSE during the helper's argument
setup. The resulting instructions and register choices matched, with every
modeled residual term zero. A copy appearing before a call in final assembly
is therefore not sufficient evidence that its source assignment preceded that
call. Renaming the locals and restoring the SDK-compatible public declaration
preserved the same compiled output.

## Acceptance is the owning-TU oracle

The scratch diagnostic still displayed `82/84` because the two recursive calls
were printed as target `jal .text@0` versus candidate `jal qsort`. Its own
`verification` field nevertheless reported whole-TU `match`, with no
differences. The existing oracle folds same-object named-symbol references
and section-relative references before comparison; see
[the assembly-splitting process](../assembly-splitting-process.md), section 3.
Do not rewrite correct recursion to chase this display-only residual. The
integrated source passed the authoritative finalization gate.

## Evidence paths

Scratch artifacts are ignored and may be cleaned; the integrated source above
preserves the decisive construction.

- Prepared m2c draft and diagnostics:
  `build/preparation/libc_52::qsort/1792265012866-2880284/`.
- Original assembly:
  `build/libraries/nonmatchings/libc_52/qsort.s` and
  `func_000001B8.s` in the same directory.
- Earlier best candidate: `build/experiments/qsort/c2.c`.
- Local-base candidate: `build/experiments/qsort/c7-local-base.c`, measurement
  `measurement-0RxIyk`; its native trace is under
  `build/compilerTrace/libc_52::qsort/`.
- Partition-after-swap candidate:
  `build/experiments/qsort/c8-partition-after-swap.c`, measurement
  `measurement-eYAht9/v2`.
- Readable candidate: `build/experiments/qsort/c9-readable.c`, measurement
  `measurement-1hqaWU/v1`.
- Integrated source: measurement `measurement-XxZ0nF/baseline`.
- Measurements above are under
  `build/pipelineReversal/libc_52::qsort/objective/`.
- Experiment history:
  `build/experimentLedger/libc_52::qsort.jsonl`.

No new original-TU grouping evidence was established: qsort and its private
helper already belong to the explicit `52-qsort.o` member. Consequently,
`notes/file-groupings.md` is unchanged; nothing here merges adjacent objects.
