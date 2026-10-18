.include "build/libraries/nonmatchings/libc_18/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_18/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/18-c24.o[0] 18-c24.o
 * sha256: b0a239e437e55c62a8149cc2428bb9b6fe806b28954f39bebb836267fffd7725
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strncmp
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strncmp.c */
#include "library/psx_bios_tailjump.h"

int strncmp(const char *arg0, const char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x18);
}

#endif
