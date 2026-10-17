# Copy helper under unmodified Homebrew Psy-Q 2.8.1

Date: 2026-10-17. Target: `lib_dacb6c202432cdbd_0::func_000001A0`.

## Outcome

**No matching-C witness has been established under this compiler.** A new common-return candidate reduces the complete member to exactly one differing instruction plus the associated local-jump relocation. This is not a match and has not been promoted.

The result identifies a concrete compiler-pass obstacle for the measured source family. It is not an exhaustive impossibility proof over every clean C program, every flag set or every historical SN build. Do not promote it to such a claim or park the production function on that basis.

## Inputs and candidate

- Original member SHA-256: `432bbcee5061fc2ba2287384b69383bcd9e5893ef0998574d032a969063fba22`.
- Compiler: the existing Homebrew Psy-Q 0.2.0 GCC 2.8.1 executable from BTN, SHA-256 `61fd8afeeeb3f86028eabf222aa6ceda5072924f1caa4553d5570a700616cbfd`.
- Existing production owner flags, including `-fforce-addr -fno-rerun-cse-after-loop`, with `-mno-split-addresses` appended for the alternative compiler.
- The original member's GAS assembler configuration, including its established `move-addu` compatibility handling. Only conflicting `.file` debug metadata is suppressed for modern GAS, as documented in `homebrew-psyq-281-trial.md`; raw compiler assembly is retained.
- Best measured clean-C candidate: `build/sn281-trial/copy-common-return.c`.
- Complete object and report: `build/sn281-trial/no-split-addresses/copy-copy-common-return/`.

The source keeps the existing two guarded byte-copy loops but uses one ordinary return after the `if/else`, rather than an early return in the backward arm. `realloc3` and the rollback helper remain unchanged and are compiled from C in the same TU. There is no function stitching, compiler mixing, hard-register pinning, inline assembly or instruction rewriting.

## Exact residual

The normal whole-member oracle reports **107/108 words**, verdict **MISMATCH**. The only `.text` word difference is:

| Section offset | Original | Candidate |
| --- | --- | --- |
| `0x170` | `08000069`: local jump to the shared return at `.text+0x1a4` | `03e00008`: `jr ra` |

The `move v0,t0` in that transfer's delay slot, both copy loops, the final shared `move v0,t0; jr ra; nop`, padding, and the other two C functions match. The required local `R_MIPS_26` relocation is consequently absent from the candidate. It must not be masked away.

A named common-return label and a one-iteration wrapper around the final return compile to the same residual. Two separate return-value assignments instead reproduce the earlier three-word residual. Adding an exhausted-counter guard before entering the forward path leaves additional conditional-branch differences; it does not provide a match. Delegating delayed-branch scheduling to GAS (`-fno-delayed-branch`) also fails, altering the whole member and its size. These are scratch experiments, not approved production flag changes.

Follow-up measurements retained the same provenance and whole-member oracle:

- `-fno-thread-jumps` on the common-return candidate still gives 107/108 with the same instruction and relocation defect. Report: `build/sn281-trial/no-split-addresses/no-thread-jumps/copy-copy-common-return/report.json`.
- `-fno-crossjumping` is rejected by this actual compiler as an invalid option. It is not a measured program variant or an available workaround.
- `build/sn281-trial/copy-counter-return.c` computes the backward result as `d + (count + 1)`, using the exhausted count rather than a direct common result. It gives 90/108, not a match; the compiler retains return-address arithmetic and changes register use. The parenthesized expression avoids forming an intermediate pointer before `d` when the exhausted count is -1. This was an alternate source hypothesis, not a replacement for the best candidate.

## Actual compiler evidence

The alternative compiler was invoked directly with `-da`, preserving its own dumps under:

`build/sn281-trial/no-split-addresses/copy-copy-common-return/sn281/trace/`

The selected `jump2` dump still has UID 61 as a normal jump to the final destination-setup block. Its `dbr` dump has replaced that transfer with a return.

Read-only GDB breakpoints on the **actual alternative binary** establish the exact calls:

1. `fill_slots_from_thread` calls `reorg_redirect_jump` for UID 61, filling the slot from the destination-setup block and redirecting the transfer.
2. `make_return_insns`, `reorg.c:4330`, calls `reorg_redirect_jump(jump, NULL)` for UID 61, requesting conversion to a return.

Observed state at the latter call:

- `reload_completed = 1`
- `profile_flag = 0`
- `regs_ever_live[31] = 0`
- `current_frame_info.total_size = 0`
- the jump pattern before redirection is `SET`.

The inspected source explains this state: `mips_can_use_return_insn()` allows the ordinary return pattern for the unprofiled frameless leaf; `make_return_insns()` attempts to convert filled jumps to the end-of-function label, retaining compatible delay-slot instructions.

Trace artifacts:

- `build/sn281-trial/copy-return-trace.gdb`
- `build/sn281-trial/copy-return-trace.log`
- `build/sn281-trial/copy-return-trace-identity.json`

**Traced and untraced assembly are byte-identical.** No debugger intervention skipped a pass, changed compiler state or changed a compiler result. Neither the compiler executable nor generated instructions were patched.

This closes the measured common-return/zero-width-tail-note family under the observed pass state. Reopen it with evidence for a different return-label or RTL construction that avoids the redirect while retaining the required program, or with independently justified compiler settings/build identity. Another spelling producing the same RTL is not new evidence.

## Semantic check, separate from matching

The exact candidate body is also included by a C89 host test, with only the `u8`/`s32` typedef header substituted. It passed **66,560** comparisons against `memmove`, including overlap in both directions, disjoint ranges, identical source/destination, zero count, and the returned destination pointer.

Artifacts: `build/sn281-trial/test-copy-semantics.c`, `host-headers/common.h`, `copy-semantics.log`.

This verifies those cases' source semantics. It is not a PSX instruction-match or production-finalization receipt and does not cover invalid/negative copy lengths.

## Status

The live function remains its original `INCLUDE_ASM` placeholder. The live compiler, source, flags and neighboring functions were not changed. No completion claim or compiler migration is justified by this result. The conditional experiment closure is recorded in the target's ledger; it does not close all source constructions or other compiler identities.
