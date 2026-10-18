.include "build/libraries/nonmatchings/libc_3/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_3/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/3-a60.o[0] 3-a60.o
 * sha256: be03f9baa1932e0cc00387fe41ca848da15e698b2969fc77c78005175e87994a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: getchar
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: getchar.c */
#include "library/psx_bios_tailjump.h"

char getchar(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3c);
}

#endif
