.include "build/libraries/nonmatchings/libc_20/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_20/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/20-c26.o[0] 20-c26.o
 * sha256: b3959df69a0279908017a4c05d06a0b22713de0621b3909095c40224e210b828
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strncpy
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strncpy.c */
#include "library/psx_bios_tailjump.h"

char *strncpy(char *arg0, const char *arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1a);
}

#endif
