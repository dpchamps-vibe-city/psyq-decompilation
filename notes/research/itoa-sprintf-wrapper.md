# libc itoa: verified decimal-formatting wrapper

Verified target: `libc_47::itoa`, 2026-10-17.

## Identity and behavior

- Original member: `library-input/redux/libc/47-itoa.o[0]`.
- Original SHA-256:
  `478423cd734dbaa4f596e257f0dbdda6df67c58020483e0ca45cc17182dc49be`.
- Matched source: `src/libraries/libc/47-itoa/itoa.c`.
- Signature: `char *itoa(int arg0)`.
- Calls `sprintf` with the member-local output buffer and the preserved `%d`
  format string, then returns that same buffer. Successive calls reuse its
  storage; callers do not receive a newly allocated string.

`RO_STR_000000B8` names the format string at `.rdata+0`.
`B_000000C8` names the buffer at `.bss+0`; the preserved zero-fill span is
`0x10` bytes. These generated names are not evidence of the original C
identifiers, and the padded storage span alone does not establish the original
array declaration's bound.

## Verification and reconstruction scope

`psx_finalize_function` passed the exact diff, configured regression build,
modification-scope and clean-source gates after the harness was reloaded.
Context publication also succeeded. The whole-member oracle reports **16/16
words, MATCH**, with no section, symbol or symbolic-relocation differences.

Only the `itoa.c` function fragment was converted. `_shared-0.h`, `_data.c`
and `tu.json` were preserved. `_data.c` still includes the canonical assembly
backlog for the member's string and buffer. Therefore this is a completed C
function with whole-member byte identity, **not** a claim that the member's
entire storage has been reconstructed in C. The verification record explicitly
has `completedFunctions: ["itoa"]` and `reconstructed: false`.

Evidence:

- `build/libraries/verified/libc_47.json`.
- `build/libraries/nonmatchings/libc_47/itoa.s`.
- `build/libraries/nonmatchings/libc_47/__library_member_data.s`.
- `build/libraries/context/libc_47/functions.h`.

No additional original translation-unit membership was established beyond the
existing member manifest, so `notes/file-groupings.md` was not changed.
