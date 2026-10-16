# REALLOC2 private resize helper: loop entry is compiler input

## Verified result and scope

`lib_51928ac182d7ab42_0::func_000000F8` is recovered in
`src/libraries/libapi/81-realloc2/func_000000F8.c`. Its 98 instruction words
match, and `psx_finalize_function` passed exact diff, full build, modification
scope and clean-source gates. Finalization identity:
`bb1acc6ce421e5592ddbfcca337c96d98b427c9632f11bc9a282872751453ef1`.
No assembler, register pinning, operation-macro exception or flag change was
needed. The byte oracle also verifies the owning TU's sections and relocations;
the neighboring copy helper remains assembly-backed.

The function rounds the requested size, reads the header before the payload,
merges following free blocks when growing, optionally extends the heap's end
block, and splits surplus space. It updates the external `_Candidate` and
`_AllocRestBlockTop` hints. The shared heap globals do not merge this member with
`MALLOC2.OBJ`, `FREE2.OBJ` or their state-owning `I_HEAP2.OBJ` neighbor.

These are measured constructions under the configured GCC 2.7.2 `-O2 -G0`
production toolchain, not a claim to have recovered Sony's historical spelling.

## The decisive distinction: three scan-loop forms

The winning control shape jumps directly into a syntactic `do` loop:

```c
if (*q != (u32)-2) {
    goto scan;
}
/* Handle the end-block case; both end-block paths share expand. */
/* ... */
goto shrink;

do {
scan:
    step = *q;
    if (!(step & 1)) {
        goto shrink;
    }
    step = (step & ~1) + 4;
    total += step;
    *p += step;
    if (total >= size) {
        goto shrink;
    }
    q = &q[*q >> 2] + 1;
} while (*q != (u32)-2);
```

The loop dump for the exact candidate explicitly reports:

> Loop at 131 ignored due to multiple entry points.

This is not equivalent compiler input to either a normally entered loop or a
plain label/backward `goto`, despite equivalent runtime behavior here:

| Measured source under `build/candidates/func_000000F8/solve/` | Observed effect |
| --- | --- |
| `v10.c` / `v16.c`: normally entered `for` / `do` | The `-2` mask moves into a preheader; the scan back edge skips its initialization. |
| `v12.c`: explicit label/backward `goto`, no syntactic loop | The mask stays in the body, but header pointer `p` and accumulated `total` exchange `$t0`/`$t1` relative to the target. Population and scheduling match; allocation does not. |
| `v20.c`: external `goto scan` into the `do` | The loop pass refuses the multiple-entry loop, retaining the mask in the body; allocation also matches. Only one commutative operand-order word remains. |
| `v22.c`, cleaned as `solved.c` | Direct split-array store fixes that word; byte-exact. |

Loop annotations still affect allocation reference weights when the loop
optimizer refuses a loop. The native `.lreg` summaries show `p` / `total`
reference counts of **9 / 5** for `v12`, versus **11 / 8** for the exact source;
the respective scheduled live lengths remain **75 / 30**. The resulting
allocation is `p=$t1`, `total=$t0`, as required. Removing the syntactic loop was
therefore not an adequate substitute for preventing its invariant motion.

## Other source boundaries that mattered

- Keep rounding stepwise: `size = bytes; size += 3; size &= ~3;`. The earlier
  single-expression rounding family folded the split's shift pair. The prior
  spelling-search closure was conditional on that single-expression premise,
  not a proof that the target's shifts were unreachable.
- Place the shared expansion body in the first end-block arm, before the scan.
  The second end-block path jumps back into it. Keeping the same body after
  the scan computes the operation but does not reproduce its layout.
- Use a fresh `newp` for the new end-block header instead of overwriting the
  scan pointer `q`. This changes value lifetimes and restored the required
  expansion register assignments.
- Load and update the same `step` variable across the free-bit test and size
  calculation. A fresh single-expression step changed scheduling/allocation.
- Preserve the shared return-value assignment: the shrink paths and the
  already-correct-size path reach `done`, while the invalid sentinel path
  retains a null result. Simplifying this into an always-initialized result
  changed return copies and delay slots.
- The last mismatch was **operand order**, not semantics or allocation:
  `split = &p[size >> 2]; split[1] = ...;` emitted `addu v1,t1,v1` at
  `.text+0x1E0`; `p[(size >> 2) + 1] = ...;` emitted the required
  `addu v1,v1,t1`. Merely reversing pointer-add operands did not change output.

These observations are scoped to the complete measured candidates. They are
not universal rules about how every equivalent expression must compile.

## Diagnostic traps to avoid

1. **There is no jump table here.** Internal transfers are direct; the only
   indirect jump in this helper is `jr $ra`. Its loads walk heap headers.
2. **Block count is not block correspondence.** In the measured harness,
   `pipeline-reversal/compare.ts` paired blocks by index, and `objective.ts`
   computed the CFG term from the absolute block-count difference. The old
   `c5.c` candidate placed expansion at `.text+0x1B8`, versus target
   `.text+0xF0`. Its report assigned 14 population differences to block 5 and
   16 to block 15, although the expansion operation existed on both sides.
   `cfg 0` did not establish corresponding blocks. Check the actual operations
   and edges before treating such a residual as missing computation.
3. **An advisory backward-branch nesting signal is not a natural-loop proof.**
   Triage called the branches to `0xF0` and `0x140` nested loops. The expansion
   at `0xF0` jumps to shrink at `0x1C4`, with no path back to its supposed
   latch. Verify dominance and reachability, not just overlapping address
   ranges. The exact C has one syntactic scan loop, not nested scan loops.
4. **Inventory parity is necessary evidence, not semantic equivalence.** Equal
   multisets of offsets, constants and shifts do not establish their dataflow,
   branch conditions or memory effects. Likewise, incomplete web correspondence
   does not license an allocator-only diagnosis.
5. **Name the address domain.** ELF `.text` starts at file offset `0x68`.
   This helper is `.text+0x90`, displayed as `0xF8` in the generated assembly;
   its successor is `.text+0x218`, displayed as `0x280`. Do not confuse a
   section-relative successor entry with a displayed address inside this helper.

## Evidence and reproduction pointers

- Original: `library-input/redux/libapi/81-realloc2.o`, SHA-256
  `f9944fff1d7f451d6d71e21a591355ae7b02747271903521a22d3e7a9bf3dc6c`.
- TU manifest: `src/libraries/libapi/81-realloc2/tu.json`.
- Original listing:
  `build/libraries/nonmatchings/lib_51928ac182d7ab42_0/func_000000F8.s`.
- Source variants: `build/candidates/func_000000F8/solve/` (`v01.c` through
  `v22.c`, plus `solved.c`). These scratch artifacts are not committed.
- Measurements under
  `build/pipelineReversal/lib_51928ac182d7ab42_0::func_000000F8/objective/`:
  `measurement-XUEJnP` (`c5`, displaced block), `measurement-cPPIii` (`v12`,
  allocation swap), `measurement-hHgR7o` (`v20`, operand order),
  `measurement-8kweDo` (`v22`, exact), `measurement-Hsk2xc` (cleaned exact).
- Native multiple-entry refusal and allocation counts:
  `build/loopTrace/lib_51928ac182d7ab42_0::func_000000F8/`, `.i.loop` and
  `.i.lreg`; plain-goto baseline in the corresponding `build/compilerTrace/`
  directory. Dumps can be overwritten by later diagnostics; check their source
  provenance before relying on them. Re-trace the committed source as needed.
- Owning-member receipt:
  `build/libraries/verified/lib_51928ac182d7ab42_0.json` (whole-member match,
  148/148 words, completed functions `realloc2` and `func_000000F8`).

Future changes must retain the whole-TU byte oracle and full finalization gate.
A scratch match or an empty normalized residual is not sufficient acceptance.
