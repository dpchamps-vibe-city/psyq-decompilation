.include "build/libraries/nonmatchings/libc_0/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_0/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/0-a56.o[0] 0-a56.o
 * sha256: fd84b9521b45512e8acc4b3c597aa0150f1449401d9ad312ce7da7d00bade1a0
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: exit
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: exit.c */
#include "library/psx_bios_tailjump.h"

void exit() {
    PSX_BIOS_TAILJUMP(0xb0, 0x38);
}

#endif
