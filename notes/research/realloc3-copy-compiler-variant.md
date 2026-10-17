# REALLOC3 byte-copy helper: compiler-variant investigation (not finalized)

## Status, 2026-10-17

Target: `lib_dacb6c202432cdbd_0::func_000001A0`.
Live destination: `src/libraries/libapi/87-realloc3/func_000001A0.c`.
The live function is still assembly-backed. **There is no production MATCH or
successful finalization for this function.** The prior `escalation-exhausted`
park is not a policy finding and does not prove a reconstruction blocker.

A clean C candidate is preserved at
`build/memmove3-reopened/guarded-labels.c`. The copy body, including operand
registers and both initial post-decrement guards, matches under the configured
Sony GCC 2.7.2. Four section words still differ in its return/jump tail.

A separate compiler experiment produces identical bytes across the helper's
entire original section range, **including section padding**, with Cygnus GCC
2.7.2-970404 (CDK). This is a positive source/compiler-pair result, not evidence
that CDK must be the original compiler. The **owning TU does not match** under
that experiment: the previously reconstructed rollback helper changes in
11 words. The verified `realloc3` body stays exact. Do not promote the scratch
candidate, replace the project compiler globally, mix compilers within this
original TU, or call this function complete.

## Semantics and recovered construction

The helper copies `count` bytes from source to destination, backward when the
destination address is at or above the source and forward otherwise. It returns
the original destination. A zero count performs no memory accesses. The caller
ignores the return value; its pointer interpretation is consistent with the
observed destination-return operation, not an independently published SDK
prototype for this private helper.

Ordinary `while (count--)` C is primary semantic evidence. Its backward indexed
loop is strength-reduced to descending pointer walks by this compiler. A guarded
label/backward-goto construction retains the target's count-indexed accesses:

```c
if (count--) {
backward_body:
    d[count] = s[count];
    if (count--) {
        goto backward_body;
    }
    return dest;
}
```

The corresponding forward arm uses the same initial post-decrement guard and
label loop with `*d++ = *s++`. This reproduces the target's initial `move v0,a2`
and decrements of the incoming count, unlike many prior experiments using
separate integer-address/count temporaries.

## Concrete compiler comparison

All experiments used the complete ordered TU, not a replacement object that
silently omits neighbors. Compiler outputs were assembled with the configured
GAS arguments and the production `move` to `addu` input rewrite. Whole `.text`
bytes were compared against the same original member.

| Compiler / candidate | Observation |
| --- | --- |
| Configured Sony GCC 2.7.2 [AL 1.1, MM 40], `guarded-labels.c` | Copy loops agree; four `.text` words differ at 0x170, 0x174, 0x1A0, 0x1A4. |
| Cygnus GCC cygnus-2.7.2-970404, same preprocessed complete TU and flags | All bytes from `.text+0x138` through `.text+0x1AF` agree, including padding. Eleven earlier words differ, all in the rollback helper. |
| Existing GCC 2.8.0-PSX / 2.8.1-PSX | Not exact; copies return directly from the backward arm and from the final arm. |
| Existing GCC 2.95.2-PSX | Not exact; additional register/setup differences. |

The CDK executable used for this read-only counterfactual is
`/home/dave/Documents/code/btn-decompilation/tools/vendor/silent-hill-decomp/tools/gcc-2.7.2-cdk/cc1`,
SHA-256 `6f11ba7ed072cc737c3d995274d380e2bd27fc1c64c04147d8cc8e89b79f8d3f`.
The harness has a public CDK build recipe at
`tools/vendor/old-gcc/gcc-2.7.2-cdk.Dockerfile` in its own repository, using
`ser-pounce/cdk-gcc` tag `b18`. The executable was not copied into production,
and no provenance equivalence between this existing binary and a fresh build
of that recipe has been asserted.

The production compiler, toolchain configuration and member overrides remain
unchanged. CDK is **not a drop-in owner-profile change** for the current C.

### Preserved artifacts

Under `build/memmove3-reopened/`:

- `ordinary.c`, `entered-do.c`, `guarded-do.c`, `guarded-labels.c`:
  semantic and loop-construction contrasts.
- `compiler-counterfactual/272-cdk/`: exact copy-range C/preprocessing,
  assembly, object, section bytes, compiler command, `byte-report.json`.
- `compiler-counterfactual/280-psx/`, `281-psx/`, and
  `gcc295-counterfactual/`: non-exact compiler contrasts.
- `flag-experiment.py` and `flag-experiment/`: Sony compiler counterfactuals
  for current flags, no-thread-jumps, no-peephole, no-expensive-optimizations,
  no-delayed-branch and O1. None settled the tail; some damage already matched
  neighboring code. These do not justify a new production override.
- `cdk-flag-counterfactual/`: CDK source/flag interaction tests. No measured
  column makes the whole current TU exact.
- `cdk-split-snapshot/`, `cdk-size-before-pointer/`,
  `cdk-snapshot-boundary/`, `cdk-snapshot-split-boundaries/`: read-only
  rollback-neighbor probes under CDK. None matched the owning member.
  No neighboring live source was changed.

The staged-objective ledger records the Sony source experiments. It does not
constitute a census of these separate manual compiler experiments.

## Return-tail mechanism and limits of the evidence

For the guarded-label source, native `.sched2` retains distinct destination
return assignments. The late `.jump2` pass shares the identical return setup;
`.dbr` then places the final `move v0,t0` in the `jr ra` slot. The target instead
has a destination move in the backward arm's jump slot, another before the final
`jr ra`, and an empty return delay slot.

The configured compiler source's `jump_optimize` invokes `find_cross_jump` with
minimum 1 for an unconditional jump to a shared label. `fill_simple_delay_slots`
searches backward through notes/standalone USEs, stopping at labels or jumps.
These explain this candidate's result. They are **not a proof over every clean
C program**, every compiler mode, or every possible original source boundary.

Extra returns, result-join variants, one-trip return wrappers, an inline hint
and several loop-entry forms did not settle this Sony tail. Repeated compiled
outputs are already recorded by the ledger; do not treat a source-family name
as a comprehensive closure.

GNU label-address/computed-goto probes were also attempted. The C guard rejects
the syntax, but direct native compilation leaves the same four word differences.
Thus that parser limitation blocks no known successful candidate here and is
not a reconstruction blocker. Do not use the refusal as evidence for a match.

## Measured harness limitations

1. **One global compiler identity.** In the current harness,
   `tools/lib/toolchain.ts` defines profiles for flags, includes and assembler
   selection. It does not permit an owner-specific compiler executable/source/
   analysis identity; its strict profile validator rejects such keys.
   `configuredTool("cc1")` selects the global tool. A clean CDK route therefore
   needs an explicit architecture decision before production integration,
   plus full owning-TU confirmation and a regression-safe compiler provenance
   model. An ad hoc compiler-dispatch wrapper is not a substitute.
2. **Inferred function extent versus section padding.** A reverse-pipeline run
   using the CDK object observes all normalized streams agreeing and no
   differing actual instruction words, but counts 29 candidate words against
   30 target words because the candidate's symbol extent excludes one padding
   nop that is present in the section. The independent section-byte comparison
   includes that nop. The owning-member oracle remains authoritative; neither
   this local false residual nor the raw section comparison is finalization.
3. **Context dependency closure.** Fresh `psx_m2c` preparation failed because its
   selected context retained `malloc3(size_t)` but omitted `size_t`'s typedef,
   reporting an unsupported K&R header. The real production TU compiles.
   Preparation failure is not an inability to reconstruct the copy helper.
4. **Qualified-name handling.** `psx_jump_trace` reports zero RTL sections for
   the member-qualified key despite `psx_compiler_trace` extracting the same
   function and preserving its native dumps. Do not interpret that failure as
   a negative compiler result.

The bounded next route is to decide whether to add owner-specific compiler
selection, then seek a **whole-member** CDK match without disturbing other
members, or continue the Sony source-state investigation. Neither route has
been declared necessary or exhausted. No policy waiver, fake byte match or
new assembly implementation has been introduced.
