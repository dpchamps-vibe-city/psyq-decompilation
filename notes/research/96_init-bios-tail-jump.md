# `_96_init` — BIOS tail-jump binding (C113.OBJ)

- Function: `lib_9892ffc60cdee207_0::_96_init`, verified identity
  `1eb7fa94b9c62f6b59655939e7f8ae8cf816891fd2f5224b3453dd6c9acefda3` (origin: agent, verification: passed).
- Finding: the C113.OBJ member is not an implementation — it is a tail-jump
  binding into the PS-X BIOS. The verified source is a single
  `PSX_BIOS_FUNCTION` stub (`src/libraries/libapi/10-c113/_96_init.c`), matching
  the earlier `InitHeap`/C57.OBJ finding.
- Evidence paths:
  - `src/libraries/libapi/10-c113/_96_init.c` (stub form).
  - `src/libraries/libapi/10-c113/_shared-0.h` (single member / single TU, `_96_init` only).
  - `library-input/redux/original-members.json`, entry `libapi/10-c113` (LIBAPI.LIB / C113.OBJ, ordinal 10).
  - `run_output/autoloop/state.json` completion record.
- Premise/condition: this classification assumes the BIOS-tail-jump probe
  evidence behind the `PSX_BIOS_FUNCTION` macro holds for the target BIOS
  version; byte-exact matching of the stub does not itself prove the ROM
  routine's identity beyond the probe.
- Corroboration (C157.OBJ / `GetConf`): a third, independent instance of the
  same pattern. `lib_8e5deca6a8677a9b_0::GetConf`, verified identity
  `123bf07d18fdeb186d5ff089a85d6bfac37863412948bbe1b0af985125d4e479` (origin:
  agent, verification: passed), is likewise a single `PSX_BIOS_FUNCTION` stub
  (`src/libraries/libapi/12-c157/GetConf.c`); the whole object is one 12-byte
  tail-jump (`build/libraries/disassembly/lib_8e5deca6a8677a9b_0/member.s`,
  `addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0x9D`).
- Corroboration (C159.OBJ / `SetMem`): a fourth, independent instance. `lib_82945d725a26a936_0::SetMem`, verified identity
  `b398b9a5e873942db3adf0771e8b876eb4840ba59ec7f3ab5b18a9c31939569b` (origin:
  agent, verification: passed), is likewise a single `PSX_BIOS_FUNCTION` stub
  (`src/libraries/libapi/13-c159/SetMem.c`, args `0xa0, 0x9f`); the whole object
  is one 12-byte tail-jump
  (`build/libraries/disassembly/lib_82945d725a26a936_0/member.s`,
  `addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0x9F`).
- Corroboration (C160.OBJ / `_boot`): a fifth, independent instance.
  `lib_bdf210249fec3f5f_0::_boot`, verified identity
  `bbcff67ec3bd705749fe61faeb869ba767d8cb60f1355257fc7453901553f908` (origin:
  agent, verification: passed), is likewise a single `PSX_BIOS_FUNCTION` stub
  (`src/libraries/libapi/14-c160/_boot.c`, args `0xa0, 0xa0`); the whole object
  is one 12-byte tail-jump
  (`build/libraries/disassembly/lib_bdf210249fec3f5f_0/member.s`,
  `addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0xA0`).
- Corroboration (C161.OBJ / `SystemError`): a sixth, independent instance.
  `lib_bbb00513fa69c2d0_0::SystemError`, verified identity
  `fedfc64925281aadf539324a35bc2d9f7d2c85c43160f26b80543325c5224409` (origin:
  agent, verification: passed), is likewise a single `PSX_BIOS_FUNCTION` stub
  (`src/libraries/libapi/15-c161/SystemError.c`, args `0xa0, 0xa1`); the whole
  object is one 12-byte tail-jump
  (`build/libraries/disassembly/lib_bbb00513fa69c2d0_0/member.s`,
  `addiu $t2,0,0xA0; jr $t2; addiu $t1,0,0xA1`).
- Corroboration (A07.OBJ / `DeliverEvent`): a seventh, independent instance.
  `lib_bea0b1ac53b09b9f_0::DeliverEvent`, verified identity
  `0c54693c349f0c7898f0c6e3b48d02726230017aa989d24353252a01463b9f79` (origin:
  agent, verification: passed), is likewise a single `PSX_BIOS_FUNCTION` stub
  (`src/libraries/libapi/21-a07/DeliverEvent.c`, args `0xb0, 0x7`); the whole
  object is one 12-byte tail-jump
  (`build/libraries/disassembly/lib_bea0b1ac53b09b9f_0/member.s`,
  `addiu $t2,0,0xB0; jr $t2; addiu $t1,0,0x7`). Note: first instance whose
  tail-jump target page is `0xB0` rather than `0xA0`, so the binding pattern
  spans more than one BIOS entry table.
- Corroboration (A08.OBJ / `OpenEvent`): an eighth, independent instance.
  `lib_86954338232a7c1b_0::OpenEvent`, verified identity
  `fbf9ac3ee507c1c61a2c6cb25a77d924d11b7174d116f45e9e988df9012a33bd` (origin:
  agent, verification: passed, full finalize gate), is likewise a single
  `PSX_BIOS_FUNCTION` stub (`src/libraries/libapi/22-a08/OpenEvent.c`, args
  `0xb0, 0x8`); the whole object is one 12-byte tail-jump
  (`build/libraries/disassembly/lib_86954338232a7c1b_0/member.s`,
  `addiu $t2,0,0xB0; jr $t2; addiu $t1,0,0x8`), sharing the `0xB0` BIOS entry
  table page with `DeliverEvent` (A07).
- Corroboration (A09.OBJ / `CloseEvent`): a ninth, independent instance.
  `lib_941bb7f9e78a6638_0::CloseEvent`, verified identity
  `02318a37423b1b2a98fa33df5bd34a238041d8ac76666a2befed7ab347fef32b` (origin:
  agent, verification: passed, full finalize gate), is likewise a single
  `PSX_BIOS_FUNCTION` stub (`src/libraries/libapi/23-a09/CloseEvent.c`, args
  `0xb0, 0x9`); the whole object is one 12-byte tail-jump
  (`build/libraries/disassembly/lib_941bb7f9e78a6638_0/member.s`,
  `addiu $t2,0,0xB0; jr $t2; addiu $t1,0,0x9`), sharing the `0xB0` BIOS entry
  table page with `DeliverEvent` (A07) and `OpenEvent` (A08). Together with
  A07/A08, this completes the contiguous event-handler cluster (ordinals
  21/22/23) at the same tail-jump shape.
- Implication: further LIBAPI members shaped as short tail-jumps should be
  checked against the BIOS tail-jump corpus before being treated as
  implementation code.
