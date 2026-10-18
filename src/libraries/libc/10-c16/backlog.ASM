.include "build/libraries/nonmatchings/libc_10/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_10/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/10-c16.o[0] 10-c16.o
 * sha256: 5c48cf42763d5826c1bb2e830e9b10163d27d486aadbab51042944e432225887
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: atoi
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: atoi.c */
#include "library/psx_bios_tailjump.h"

int atoi(const char *arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x10);
}

#endif
