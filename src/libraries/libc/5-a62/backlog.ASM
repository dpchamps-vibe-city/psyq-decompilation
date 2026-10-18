.include "build/libraries/nonmatchings/libc_5/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_5/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/5-a62.o[0] 5-a62.o
 * sha256: dcbeb87139f137463a731882012195eafdc406cc4734f743e109e0b13913f849
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: gets
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: gets.c */
#include "library/psx_bios_tailjump.h"

char *gets(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3e);
}

#endif
