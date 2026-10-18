.include "build/libraries/nonmatchings/libc_38/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_38/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/38-c48.o[0] 38-c48.o
 * sha256: 7354cff2be53298053fa74beed900da3da82618225bebcf7155ffa2b673f36c8
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: srand
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: srand.c */
#include "library/psx_bios_tailjump.h"

void srand(unsigned int arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x30);
}

#endif
