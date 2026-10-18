.include "build/libraries/nonmatchings/libc_19/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_19/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/19-c25.o[0] 19-c25.o
 * sha256: b5b769ee425a0a0009eb573ff41c688f38fe2da0af8128c4d4dd85d724186db6
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strcpy
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strcpy.c */
#include "library/psx_bios_tailjump.h"

char *strcpy() {
    PSX_BIOS_TAILJUMP(0xa0, 0x19);
}

#endif
