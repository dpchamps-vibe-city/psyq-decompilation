# libgs_95::GsSortObject4J — agent-approved exemption, awaiting ratification

- **Approved:** 2026-10-25T11:39:31.289Z
- **Approved by:** deepseek-v4-1-flash-1017 (one rung above the tier that proposed it)
- **Constructs:** flag-override

## Rationale given

The -mhard-float per-TU override is the documented, evidence-bound exception class, not a spelling workaround. Original bytes (GsSortObject4J.s) show an 88-byte frame (addiu $29,$29,-0x58 at :370) with exactly 10 saved registers ($16-$23,$30,$31 at :378-382), and four preheader hoisted pointer/index values stored to frame slots 0x20..0x2C (:476-479) then reloaded per handler (lw 0x20($29) at :503, 0x24 at :528, 0x28 at :516, 0x2C at :552). The candidate compiled under -mhard-float reproduces all three fingerprints exactly: .frame $sp,88,$31 with regs=10/0 mask 0xc0ff0000 (candidate .s:3-16), and the same four stores sw 32/36/40/44($sp) (:129-132). The recorded counterfactual on the same source under the default -msoft-float yields frame 0x50 and 271/426, i.e. the four hoists and the 0x58/10-register layout disappear. Mechanism: -mhard-float makes the 32 FP registers allocatable, raising n_non_fixed_regs so loop.c/regalloc hoists these invariants; with no COP2/FP value present the only effect is this structural heuristic — matching the identical, already-established witnesses libcd_1, libds_5, libgpu_2, libgpu_3 (and the libgs_94 sibling, parked only for lack of an adjudicating tier). This override independently reproduces original structure and is orthogonal to the residual shared-tail idiom, so approving the flag asserts the compile flag is correct here without claiming the function byte-matches. Adding the allowlist entry to .pi/autoloop.json sourcePolicy.allowlist for CC1FLAGS_libgs_95 is the correct disposition.

## Why this is filed rather than applied

The loop honours this exemption for the rest of its own run, but it does not write it
into `.pi/autoloop.json`. That allowlist is a permanent assertion that the construct is
the correct answer for this function, and only a human makes that assertion. Ratify it by
adding the entry there, or reject it by re-opening the function.
