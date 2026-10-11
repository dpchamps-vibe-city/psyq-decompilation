# InitHeap: historical diagnostics — superseded by BIOS macro support

Current status: the explicitly approved `PSX_BIOS_FUNCTION` candidate reproduces all four original words and passes whole-member program comparison and source policy. The live source remains an unfinalized stub. No human approval is pending; the unsupported-target findings below predate macro support.

Target: `lib_6f830259724bafe6_0::InitHeap`
Live destination (unchanged): `src/libraries/libapi/0-c57.c`

## Corrected status after retry

The updated tools classify this as an **unsupported clean-C target**, not an assembly-policy approval request. The earlier request to retain `INCLUDE_ASM` is withdrawn. No exception has been granted or added, and the unchanged stub must not be counted as reconstructed. Completing it requires supported compiler representation of the fixed-register BIOS calling convention; an unsupported result is not a byte match.

## Independently checked evidence

- `library-input/psyq/INCLUDE/MALLOC.H:21` declares `void InitHeap(unsigned long *, unsigned long)`.
- The original owning object is `build/libraries/originals/lib_6f830259724bafe6_0/75de3c620e849a420e64f9a62a0806f94bfb7d6956753d8bb430ee526406949a.o`.
- `readelf -W -h -S -s -r -x .text` reports an ELF32 little-endian MIPS relocatable object, one global `InitHeap` symbol at `.text+0`, `.text` length 16, and no relocations.
- Its complete `.text` bytes are `a0000a24 08004001 39000924 00000000`, corresponding to:

  ```asm
  addiu $t2, $zero, 0xA0
  jr    $t2
   addiu $t1, $zero, 0x39
  nop
  ```

- The veneer leaves the incoming argument registers and return address intact, transfers without linking to absolute address `0xA0`, and sets `$t1` to `0x39` in the jump delay slot. The fixed-register selector is part of the BIOS calling convention, not a third ordinary C argument.
- `.pi/autoloop.json` has an empty `sourcePolicy.allowlist`. Its existing memory-barrier and stack-pointer allowances do not cover this veneer.

Ordinary C does not express this fixed-register BIOS selector operation. Replacing it with an ordinary indirect call would not preserve that contract; writing the selector with register pinning or assembly requires human authorization. No inaccurate C surrogate or new assembly implementation has been authored.

## Measurement status and bounded results

On retry, header lookup and library-mode reconstruction work. Fresh m2c generation still fails on `jr $t2`; no measured C source exists. Fresh triage reports a `bios-veneer` blocker. Callee truth finds zero direct callees. Reconstruction resolves the owning member (`.text+0x0`, 16 bytes) and returns **STATE: unsupported-target**, identifying the tail-jump to `0xA0` with `$t1=0x39`, preserving incoming arguments and `$ra`. It evaluated zero candidates and performed zero compiles (130 ms). This is not an exhausted clean-C source-shape domain. The earlier `target_path` diagnostic failure is superseded by this successful target analysis.

Residual key: **unavailable — no C candidate compiled**. Control-flow, population, scheduling, and allocation axes: **not measured; none claimed closed**. No byte-match or finalization claim is made for the unchanged `INCLUDE_ASM` stub.

Fresh prepared evidence: `build/preparation/lib_6f830259724bafe6_0::InitHeap/1791687668776-2667604/evidence.md`; the corresponding `triage.stdout` contains the BIOS-veneer blocker. Both reconstruction results and their scoped premises are recorded in the experiment ledger.
