.include "build/libraries/nonmatchings/libc_32/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_32/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/32-c39.o[0] 32-c39.o
 * sha256: ebcb70701ec60f977d30ad1b3a2d27d217093cf9224cb0068faa7b18f5a84c66
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: bcopy
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: bcopy.c */
#include "library/psx_bios_tailjump.h"

void *bcopy(const unsigned char *arg0, unsigned char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x27);
}

#endif
