.include "build/libraries/nonmatchings/libc_23/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_23/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/23-c29.o[0] 23-c29.o
 * sha256: 520e4a14c49d7c64124a7aa8ec4b0f4b078ec7a77d8ec5fd9e0ba1aa36a247d0
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: rindex
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: rindex.c */
#include "library/psx_bios_tailjump.h"

char *rindex(const char *arg0, char arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1d);
}

#endif
