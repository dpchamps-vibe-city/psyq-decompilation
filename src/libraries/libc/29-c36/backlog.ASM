.include "build/libraries/nonmatchings/libc_29/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_29/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/29-c36.o[0] 29-c36.o
 * sha256: 1b0e72dc1a9af15424b587137ee6e55aa83e3da6be46fe563f3cb14c1123a686
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strstr
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strstr.c */
#include "library/psx_bios_tailjump.h"

char *strstr(const char *arg0, const char *arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x24);
}

#endif
