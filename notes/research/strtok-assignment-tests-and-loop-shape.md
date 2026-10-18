# STRTOK: assignment tests and syntactic loops, not forced load spellings

## Verified result

- Target: `libc_51::strtok`, LIBC's `51-strtok.o`.
- Source: `src/libraries/libc/51-strtok/strtok.c`.
- Owned declaration: `include/library/51-strtok.h`. The saved pointer's original
  data fragment remains assembly-backed; neighboring fragments were not changed.
- `psx_finalize_function` passed exact diff, full build, modification scope and
  clean-source gates. Supplied source/evidence identity:
  `149800f736489e70c4af345e1835c2801d1320840b7d47ee245b3565016f6327`.
- Whole-member receipt: `build/libraries/verified/libc_51.json`,
  `MATCH`, **72/72 words**, including sections and symbolic relocations. Its
  separate whole-member identity is
  `fbd10d40e2b085b7210751d674b72a9c977dde6bfec0efe276d80c2e758ba6cc`.
- Source SHA-256:
  `909d7b5f6985dc22d0b1f355c78f8508291ed7f8fe82dd218a905ba8cb138249`.
- Original object SHA-256:
  `576979ef9a64e4835b49b4d515e486bf57064a96b145685c772cbcd76a6b8bae`.

This is a measured clean-C construction under the configured
`trunk-19970318` GCC, `-O2 -G0 -funsigned-char`, and production assembler path.
It is not proof of Sony's historical source spelling. No flags, compiler,
assembler, register pinning or policy exceptions were changed.

## What actually closed the residual

The previous session understood tokenization, but tried to reproduce the
optimizer's loads explicitly. Its preferred `build/strtok-ws/q1.c` used:

```c
u8 c;
c = *s++;
if (*(s8 *)(s - 1) == 0) { /* exit */ }
```

That generated an increment followed by `lb -1(s)`. The target instead loads
both unsigned and signed values from `0(s)`, branches on the signed load, and
increments `s` in the branch delay slot. Equivalent byte addresses at runtime
are not equivalent compiler input.

### 1. Restore the narrowing assignment expression

Declare the saved character as **`s8`**, and test the assignment itself:

```c
s8 character;
if ((character = *s++) == 0) {
    break;
}
```

The incoming pointer remains `u8 *`. This expresses one fetch, narrowing to a
signed character, the test of that assignment value, and the postincrement.
There is no second source dereference of `s - 1` to place after the increment.

Measured as `build/strtok-solve/assigned-char.c`, this restored the required
first-phase fetch sequence, delay-slot increment and register choices. The
remaining differences were in the second token-scan phase. The full residual
still had degraded block correspondence; it was not yet an allocation-only
near-match.

The exact source's native `.rtl` records both fetches as the same operation
family: UID 42 / UID 168 assign `mem:QI (reg/v:SI 82)` to character pseudo 85;
UIDs 45–46 / 171–172 sign-extend the assignment value; UIDs 47 / 173 increment
the pointer; UIDs 49 / 175 test the extended value. These are candidate-side
observations, not recovered RTL from the original object.

### 2. Restore the second phase's syntactic loop

The intermediate candidate still represented the token scan as labels and
backward gotos. Replace that outer control flow with a real `while`, retaining
the shared termination block before it:

```c
goto scan;
terminate_token:
    s[-1] = 0;
    D_00000190 = s;
    return (char *)token;
scan:
    while ((character = *s++) != 0) {
        /* Scan delimiters; jump to terminate_token on equality. */
    }
D_00000190 = 0;
return (char *)token;
```

This one region rewrite produced **72/72 exact**, with all residual terms zero.
The delimiter loops and first phase were otherwise retained. The winning
source still uses an unsigned delimiter-character local and signed comparisons;
this session did not establish that every remaining cast or local is necessary.

The native trace of the integrated exact source has **four syntactic loop
records, maximum depth two**. `psx_loop_trace` reports the invariant character
sign-extension pair moved out of each delimiter loop (original UIDs 80/81 and
201/202). In the second phase, `.i.loop` places the hoisted pair at UIDs
287/288 between the outer loop and inner `NOTE_INSN_LOOP_BEG`. A label/backward
goto version did not reproduce this output. Thus removing the loop construct
was not a harmless transcription choice for this measured candidate.

## Why the earlier search was misleading

- **The draft had a real delay-slot transcription defect.** It incremented
  the pointer and then tested the next byte, whereas the target tested the
  current byte before its delay-slot increment. Fixing undefined `NULL` only
  made that draft compile; it did not fix its meaning.
- **The target's redundant-looking loads were achievable without tricks.**
  Trying to force them through separate signed/unsigned dereferences obscured
  the ordinary signed-character assignment test that produced them.
- **The low population number was not reliable block attribution.** `q1.c`
  reported `cfg 1, pop 5, sched 0, alloc 4`, but also target 21 versus candidate
  20 blocks and explicitly degraded correspondence. The pipeline reversal
  classified instruction population as the provisional owner, with no verified
  pre-delay-slot round trip. It did not authorize allocator-only work.
- **Repeated spelling changes were not new compiler experiments.** The earlier
  `strtok` run made 48 residual-objective calls; 15 candidate results explicitly
  repeated machine words already measured. Declaration-order permutations at
  the end all reproduced `q1.c`.
- **Tool refusals were capability limits, not impossibility proofs.** The
  reconstruction engine refused symbolic ET_REL storage; family transfer
  required an executable; shape synthesis lacked the selected scratch C; the
  control-tail sweep had no supported return tail. None ruled out clean C.
- **The flag probe did not justify an override.** Some nominated options were
  unsupported by this compiler; its conclusion was inconclusive. The source
  changes above matched under the unchanged baseline.

## Evidence and reproduction

Scratch candidates and reports are under `build/` and may not survive cleanup.
The integrated source and this note preserve the decisive constructions.

| Candidate | Measurement directory under `build/pipelineReversal/libc_51::strtok/objective/` | Result |
| --- | --- | --- |
| Prior `q1.c` | `measurement-VxjLOK` | CFG mismatch; explicit `lb -1(s)` reads |
| `assigned-char.c` | `measurement-0AgJ15` | First-phase shape restored; second phase still differs |
| `structured-token.c` | `measurement-uWMUM0` | Whole-member exact |
| Cleaned `integrated.c` | `measurement-xRcccN` | Whole-member exact, same compiled output |
| Integrated live source | `measurement-YV0HiI` | Whole-member exact |

Additional evidence:

- Original assembly:
  `build/libraries/nonmatchings/libc_51/strtok.s`.
  Displayed addresses include the object file offset; e.g. displayed `0xE4`
  is `.text+0x74`, and displayed `0x15C` is `.text+0xEC`.
- Prepared draft and diagnostic evidence:
  `build/preparation/libc_51::strtok/1792263100517-2800909/`.
- Exact-source native dumps and report:
  `build/compilerTrace/libc_51::strtok/`.
- Exact-source loop report:
  `build/loopTrace/libc_51::strtok/`.
- Experiment history:
  `build/experimentLedger/libc_51::strtok.jsonl`.

No new cross-function or original-TU grouping evidence was established, so
`notes/file-groupings.md` is unchanged. The private saved pointer belongs to
the already-known member; recovering its use does not merge adjacent objects.

For future matching-agent sessions, see [the tricky-spelling checklist](../agent-guidance.md).
