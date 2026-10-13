# Original translation-unit groupings

Groups follow original object membership, not shared function names or library-wide similarity. Original C source filenames are unknown. A shared BIOS vector, similar implementation, or adjacent archive ordinal does not merge separate objects into one TU.

The automatic sweep covered all 2,671 identifiable functions and integrated 115 new exact matches. Its results and per-candidate gate paths are in `build/static-sweep/report.json`; a concise retained summary is in `notes/research/static-sweep-2026-10-11.md`. Partial groups below list unrecovered neighbors explicitly. Whole-member byte identity with original backlog does not mean those neighbors are decompiled.

## LIBAPI.LIB — C57.OBJ (ordinal 0)

- Reconstructed source: `src/libraries/libapi/0-c57/InitHeap.c`
- Target member: `lib_6f830259724bafe6_0`
- Members:
  - `InitHeap` — BIOS heap-initialization binding; the allocator implementation is in ROM, not this object.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/0-c57`, identifies `LIBAPI.LIB` / `C57.OBJ`, ordinal 0. The selected converted object, `library-input/redux/libapi/0-c57.o`, contains only `InitHeap`; see `build/libraries/disassembly/lib_6f830259724bafe6_0/member.s`.
- Verification: `build/finalization/InitHeap.json` records exact function and whole-member MATCH, passing scope/source-policy gates, and published context. Converted target SHA-256: `75de3c620e849a420e64f9a62a0806f94bfb7d6956753d8bb430ee526406949a`.

## LIBAPI.LIB — C113.OBJ (ordinal 10)

- Reconstructed source: `src/libraries/libapi/10-c113/_96_init.c`
- Target member: `lib_9892ffc60cdee207_0`
- Members:
  - `_96_init` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Mirrors the `InitHeap` (C57) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/10-c113`, identifies `LIBAPI.LIB` / `C113.OBJ`, ordinal 10. `src/libraries/libapi/10-c113/_shared-0.h` records one original member, one TU, functions: `_96_init`; baseline `library-input/converted/lib/libapi/c113.o` is unambiguously named.
- Verification: passed (agent origin, verified identity `1eb7fa94b9c62f6b59655939e7f8ae8cf816891fd2f5224b3453dd6c9acefda3`); completion recorded in `run_output/autoloop/state.json`.

## LIBAPI.LIB — C157.OBJ (ordinal 12)

- Reconstructed source: `src/libraries/libapi/12-c157/GetConf.c`
- Target member: `lib_8e5deca6a8677a9b_0`
- Members:
  - `GetConf` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Third member of the `InitHeap` (C57) / `_96_init` (C113) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/12-c157`, identifies `LIBAPI.LIB` / `C157.OBJ`, ordinal 12. `src/libraries/libapi/12-c157/_shared-0.h` records one original member, one TU, functions: `GetConf`; baseline `library-input/converted/lib/libapi/c157.o` is unambiguously named. `build/libraries/disassembly/lib_8e5deca6a8677a9b_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0x9D`), consistent with a binding-only TU.
- Verification: passed (agent origin, verified identity `123bf07d18fdeb186d5ff089a85d6bfac37863412948bbe1b0af985125d4e479`); completion recorded in `run_output/autoloop/state.json`.

## LIBAPI.LIB — C159.OBJ (ordinal 13)

- Reconstructed source: `src/libraries/libapi/13-c159/SetMem.c`
- Target member: `lib_82945d725a26a936_0`
- Members:
  - `SetMem` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Fourth member of the `InitHeap` (C57) / `_96_init` (C113) / `GetConf` (C157) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/13-c159`, identifies `LIBAPI.LIB` / `C159.OBJ`, ordinal 13. `src/libraries/libapi/13-c159/_shared-0.h` records one original member, one TU, functions: `SetMem`; baseline `library-input/converted/lib/libapi/c159.o` is unambiguously named. `build/libraries/disassembly/lib_82945d725a26a936_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0x9F`), consistent with a binding-only TU and matching the stub's `(0xa0, 0x9f)` arguments.
- Verification: passed (agent origin, verified identity `b398b9a5e873942db3adf0771e8b876eb4840ba59ec7f3ab5b18a9c31939569b`); completion recorded in `run_output/autoloop/state.json`.

## LIBAPI.LIB — C160.OBJ (ordinal 14)

- Reconstructed source: `src/libraries/libapi/14-c160/_boot.c`
- Target member: `lib_bdf210249fec3f5f_0`
- Members:
  - `_boot` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Fifth member of the `InitHeap` (C57) / `_96_init` (C113) / `GetConf` (C157) / `SetMem` (C159) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/14-c160`, identifies `LIBAPI.LIB` / `C160.OBJ`, ordinal 14. `src/libraries/libapi/14-c160/_shared-0.h` records one original member, one TU, functions: `_boot`; baseline `library-input/converted/lib/libapi/c160.o` is unambiguously named. `build/libraries/disassembly/lib_bdf210249fec3f5f_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0xA0`), consistent with a binding-only TU and matching the stub's `(0xa0, 0xa0)` arguments.
- Verification: passed (agent origin, verified identity `bbcff67ec3bd705749fe61faeb869ba767d8cb60f1355257fc7453901553f908`); completion recorded in `run_output/autoloop/state.json`.

## LIBAPI.LIB — C161.OBJ (ordinal 15)

- Reconstructed source: `src/libraries/libapi/15-c161/SystemError.c`
- Target member: `lib_bbb00513fa69c2d0_0`
- Members:
  - `SystemError` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Sixth member of the `InitHeap` (C57) / `_96_init` (C113) / `GetConf` (C157) / `SetMem` (C159) / `_boot` (C160) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/15-c161`, identifies `LIBAPI.LIB` / `C161.OBJ`, ordinal 15. `src/libraries/libapi/15-c161/_shared-0.h` records one original member, one TU, functions: `SystemError`; baseline `library-input/converted/lib/libapi/c161.o` is unambiguously named. `build/libraries/disassembly/lib_bbb00513fa69c2d0_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0xA1`), consistent with a binding-only TU and matching the stub's `(0xa0, 0xa1)` arguments.
- Verification: passed (agent origin, verified identity `fedfc64925281aadf539324a35bc2d9f7d2c85c43160f26b80543325c5224409`); completion recorded in `run_output/autoloop/state.json`.

## LIBAPI.LIB — A07.OBJ (ordinal 21)

- Reconstructed source: `src/libraries/libapi/21-a07/DeliverEvent.c`
- Target member: `lib_bea0b1ac53b09b9f_0`
- Members:
  - `DeliverEvent` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Seventh member of the `InitHeap` (C57) / `_96_init` (C113) / `GetConf` (C157) / `SetMem` (C159) / `_boot` (C160) / `SystemError` (C161) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/21-a07`, identifies `LIBAPI.LIB` / `A07.OBJ`, ordinal 21. `src/libraries/libapi/21-a07/_shared-0.h` records one original member, one TU, functions: `DeliverEvent`; baseline `library-input/converted/lib/libapi/a07.o` is unambiguously named. `build/libraries/disassembly/lib_bea0b1ac53b09b9f_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xB0; jr $t2; addiu $t1,0,0x7`), consistent with a binding-only TU and matching the stub's `(0xb0, 0x7)` arguments.
- Verification: passed (agent origin, verified identity `0c54693c349f0c7898f0c6e3b48d02726230017aa989d24353252a01463b9f79`); completion recorded in `run_output/autoloop/state.json`.

## LIBAPI.LIB — A08.OBJ (ordinal 22)

- Reconstructed source: `src/libraries/libapi/22-a08/OpenEvent.c`
- Target member: `lib_86954338232a7c1b_0`
- Members:
  - `OpenEvent` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Eighth member of the `InitHeap` (C57) / `_96_init` (C113) / `GetConf` (C157) / `SetMem` (C159) / `_boot` (C160) / `SystemError` (C161) / `DeliverEvent` (A07) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/22-a08`, identifies `LIBAPI.LIB` / `A08.OBJ`, ordinal 22. `src/libraries/libapi/22-a08/_shared-0.h` records one original member, one TU, functions: `OpenEvent`; baseline `library-input/converted/lib/libapi/a08.o` is unambiguously named. `build/libraries/disassembly/lib_86954338232a7c1b_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xB0; jr $t2; addiu $t1,0,0x8`), consistent with a binding-only TU and matching the stub's `(0xb0, 0x8)` arguments.
- Verification: passed (agent origin, verified identity `fbf9ac3ee507c1c61a2c6cb25a77d924d11b7174d116f45e9e988df9012a33bd`); full finalize gate passed.

## LIBAPI.LIB — A09.OBJ (ordinal 23)

- Reconstructed source: `src/libraries/libapi/23-a09/CloseEvent.c`
- Target member: `lib_941bb7f9e78a6638_0`
- Members:
  - `CloseEvent` — BIOS tail-jump binding (reconstructed as a `PSX_BIOS_FUNCTION` stub); the real implementation lives in ROM, not this object. Ninth member of the `InitHeap` (C57) / `_96_init` (C113) / `GetConf` (C157) / `SetMem` (C159) / `_boot` (C160) / `SystemError` (C161) / `DeliverEvent` (A07) / `OpenEvent` (A08) pattern of a library member that is a binding rather than an implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/23-a09`, identifies `LIBAPI.LIB` / `A09.OBJ`, ordinal 23. `src/libraries/libapi/23-a09/_shared-0.h` records one original member, one TU, functions: `CloseEvent`; baseline `library-input/converted/lib/libapi/a09.o` is unambiguously named. `build/libraries/disassembly/lib_941bb7f9e78a6638_0/member.s` shows a three-instruction BIOS tail transfer (excluding padding) (`addiu $t2,0,0xB0; jr $t2; addiu $t1,0,0x9`), consistent with a binding-only TU and matching the stub's `(0xb0, 0x9)` arguments. Shares the `0xB0` BIOS entry table page and contiguous link-order ordinals (A07/A08/A09 = 21/22/23) with `DeliverEvent` and `OpenEvent` — the three form the event-handler binding cluster in the library's original member order.
- Verification: passed (agent origin, verified identity `02318a37423b1b2a98fa33df5bd34a238041d8ac76666a2befed7ab347fef32b`); full finalize gate passed.

## LIBAPI.LIB — COUNTER.OBJ (ordinal 72)

- TU directory: `src/libraries/libapi/72-counter/`; target `lib_f5b70e00e12530c5_0`.
- Original functions: `SetRCnt`, `GetRCnt`, `StartRCnt`, `StopRCnt`, `ResetRCnt`.
- Recovered: `GetRCnt` — reads the `count` field of the root-counter record selected by the low argument half-word, returning 0 for counter indices 3 and above. `StartRCnt` — ORs the per-counter enable bit from `D_000001E8` into the enable register at `D_000001E0`, returning whether the index is below 3. `SetRCnt` — writes the selected root-counter record's `mode` and `target` fields (via the shared `D_000001E4` struct) from the value and flags arguments, returning 0 for counter indices 3 and above.
- Remaining functions (`StopRCnt`, `ResetRCnt`) and the shared member data remain original assembly backlog.
- Same-file evidence: all five functions share one original object and one `.data` cluster — `D_000001E0` (MMIO 0x1F801070 enable register pointer), `D_000001E4` (MMIO 0x1F801100 counter-array pointer), `D_000001E8` (enable-bit table `{0x10, 0x20, 0x40, 0x100}`) — declared once in `_shared-0.h` and stored in `_data.c`.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/72-counter`, identifies `LIBAPI.LIB` / `COUNTER.OBJ`, ordinal 72. `_shared-0.h` records one original member, one TU, and object sha256 `f9696b5b2525f5948c2e265374583b643e5fe7484870ce81a921db325f1c6c2b`; `tu.json` lists the ordered parts.
- Verification: `StartRCnt` passed the full finalize gate (agent origin, verified identity `11f9ac41d9aeac777ba8bdd106a803dc911f518e6829e823cd99eb3be19ae7e2`); `GetRCnt` was integrated in the same verified change set. `SetRCnt` passed the full finalize gate (agent origin, verified identity `2605376483c945b31829ee60d1506aae9d9707f395f690c995462ceb614bc67a`); the verified body reuses the already-documented `D_000001E4` record cluster, so no new TU-membership evidence was introduced.

## LIBAPI.LIB — SC2B.OBJ (ordinal 73)

- TU directory: `src/libraries/libapi/73-sc2b/`; target `lib_b98fea1557178089_0`.
- Original function: `SetConf` (the only named function); same-object neighbors `func_00000290`, `func_000002AC`, `func_000002C8`, `func_000002E4`, `func_00000300`, `func_0000031C`, `func_00000350`, `func_0000036C` remain assembly backlog.
- Recovered: `SetConf` — initializes the member's root configuration record `D_000003A0` and its header/index/sub-tables, returning 1 on success.
- Same-file evidence: the verified body reads and writes the member's own root record `D_000003A0` (offset 0x3A0, the SC2B `.data` cluster declared in `_shared-0.h` and stored in `_data.c`), tying the recovered body to this member rather than to another LIBAPI object.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/73-sc2b`, identifies `LIBAPI.LIB` / `SC2B.OBJ`, ordinal 73, `ambiguousNamedBaseline: false`; `src/libraries/libapi/73-sc2b/_shared-0.h` records one original member, one TU, functions: `SetConf`, and `tu.json` lists the ordered parts.
- Verification: passed (agent origin, verified identity `346b829e5b9a4cde3149c54eee56768112f34882ab87a7bf7d914b20f9ba8f58`); full finalize gate passed.

## LIBAPI.LIB — PAD.OBJ (ordinal 76)

- TU directory: `src/libraries/libapi/76-pad/`; target `lib_a8f7345a144556eb_0`.
- Original functions: `SetInitPadFlag`, `ReadInitPadFlag`, `PAD_init`, `InitPAD`, `StartPAD`.
- Recovered: `ReadInitPadFlag` — reads the member's `D_00000300` initialization flag.
- Remaining functions and member data are still original assembly backlog.
- Membership evidence: `library-input/redux/original-members.json`, entry `libapi/76-pad`, and the ordered `tu.json`. Sweep finalization passed for `ReadInitPadFlag`, including the owning member with its unrecovered neighbors.

## LIBC2.LIB — RAND.OBJ (ordinal 14)

- TU directory: `src/libraries/libc2/14-rand/`; target `lib_caa9d705cf395a2f_0`.
- Original functions: `rand`, `srand`.
- Recovered: `rand` — updates `B_000000B0` using `state * 0x41C64E6D + 0x3039`, then returns `(state >> 16) & 0x7FFF`.
- `srand` and the backing BSS remain assembly backlog. Original `srand` stores its argument to the same state symbol, establishing the shared-state group.
- Membership evidence: `library-input/redux/original-members.json`, entry `libc2/14-rand`, `tu.json`, and `build/libraries/disassembly/lib_caa9d705cf395a2f_0/member.s`. Sweep finalization passed for `rand`.
- Do not merge this implementation with LIBC.LIB's separate C47.OBJ / C48.OBJ `rand` / `srand` BIOS bindings merely because the public names agree.

## LIBDS.LIB — DSREADY.OBJ (ordinal 11)

- TU directory: `src/libraries/libds/11-dsready/`; target `lib_2c90443875239758_0`.
- Original functions: `DsStartReadySystem`, `DsEndReadySystem`, `DsReadySystemMode`, `ER_active`, `ER_clear`.
- Recovered: `ER_active` — reads `D_00000630`.
- Other functions and member data remain assembly backlog; the getter alone does not establish the full ready-system behavior.
- Membership evidence: `library-input/redux/original-members.json`, entry `libds/11-dsready`, and `tu.json`. Sweep finalization passed for `ER_active`.

## LIBETC.LIB — VMODE.OBJ (ordinal 6)

- TU directory: `src/libraries/libetc/6-vmode/`; target `lib_033d4f3f087a4c4b_0`.
- Original functions: `SetVideoMode`, `GetVideoMode`.
- Recovered: `GetVideoMode` — reads `D_000000A0`.
- `SetVideoMode` and member data remain assembly backlog.
- Membership evidence: `library-input/redux/original-members.json`, entry `libetc/6-vmode`, and `tu.json`. Sweep finalization passed for `GetVideoMode`.

## LIBHMD.LIB — SCANUNIT.OBJ (ordinal 575)

- TU directory: `src/libraries/libhmd/575-scanunit/`; target `lib_ed0eebebae6499a6_0`.
- Original functions: `GsScanUnit`, `GsGetHeadpUnit`.
- Recovered: `GsGetHeadpUnit` — returns the pointer stored in `D_00000248`.
- `GsScanUnit` and member data remain assembly backlog; no structure layout or traversal behavior is inferred from the pointer getter.
- Membership evidence: `library-input/redux/original-members.json`, entry `libhmd/575-scanunit`, and `tu.json`. Sweep finalization passed for `GsGetHeadpUnit`.

## LIBSND.LIB — VM_VIB.OBJ (ordinal 203)

- TU directory: `src/libraries/libsnd/203-vm_vib/`; target `lib_5062f444b23e65cf_0`.
- Original functions, all recovered: `SeVibOn`, `SetVib`, `SsUtVibrateOn`, `SsUtVibrateOff` — return-only no-ops in this supplied member.
- The empty C bodies reproduce original `jr $ra; nop` pairs; they are not placeholder implementations. These bytes establish no vibration implementation elsewhere and do not determine unread argument contracts.
- Membership evidence: `library-input/redux/original-members.json`, entry `libsnd/203-vm_vib`, `tu.json`, and `build/libraries/disassembly/lib_5062f444b23e65cf_0/member.s`. Sweep finalization passed separately as each function was integrated.

## LIBSND.LIB — SSCLOSE.OBJ (ordinal 51)

- TU directory: `src/libraries/libsnd/51-ssclose/`; target `lib_d54eaa3c6fb04732_0`.
- Original named functions: `SsSeqClose`, `SsSepClose`.
- Recovered: `SsSepClose` — forwards its short argument to `func_00000068`.
- `SsSeqClose` remains assembly backlog; this forwarding wrapper does not reconstruct the close implementation.
- Membership evidence: `library-input/redux/original-members.json`, entry `libsnd/51-ssclose`, and `tu.json`. Sweep finalization passed for `SsSepClose`.

## LIBSPU.LIB — S_IT.OBJ (ordinal 58)

- TU directory: `src/libraries/libspu/58-s_it/`; target `lib_b10ef9bfc233ef62_0`.
- Original functions: `_spu_setInTransfer`, `_spu_getInTransfer`.
- Recovered: `_spu_getInTransfer` — returns whether `_spu_inTransfer` differs from 1.
- `_spu_setInTransfer` remains assembly backlog. The shared external flag does not establish ownership of its backing storage in this member.
- Membership evidence: `library-input/redux/original-members.json`, entry `libspu/58-s_it`, and `tu.json`. Sweep finalization passed for `_spu_getInTransfer`.

## LIBSPU.LIB — S_GTSA.OBJ (ordinal 52)

- Reconstructed source: `src/libraries/libspu/52-s_gtsa/SpuGetTransferStartAddr.c`; target `lib_35b5022272f9bbf5_0`.
- Original function: `SpuGetTransferStartAddr` — returns `_spu_tsa` shifted by `_spu_mem_mode_plus`.
- Membership evidence: `library-input/redux/original-members.json`, entry `libspu/52-s_gtsa`, and `tu.json`. This previously matched function was preserved through the TU-directory migration and recorded as already complete by the sweep.
