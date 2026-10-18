.include "build/libraries/nonmatchings/libc_16/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_16/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/16-c22.o[0] 16-c22.o
 * sha256: 70bf5949a157bacdb71a7af93c3650efa280044b46d58359f573ec3eb510098b
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strncat
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strncat.c */
#include "library/psx_bios_tailjump.h"

char *strncat(char *arg0, const char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x16);
}

#endif
