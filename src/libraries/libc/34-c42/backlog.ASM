.include "build/libraries/nonmatchings/libc_34/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_34/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/34-c42.o[0] 34-c42.o
 * sha256: 332c6e34b016662669012231f8674869da6c5996731b2a3bd1ebc9f5b02c6a33
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: memcpy
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: memcpy.c */
#include "library/psx_bios_tailjump.h"

void *memcpy() {
    PSX_BIOS_TAILJUMP(0xa0, 0x2a);
}

#endif
