.include "build/libraries/nonmatchings/libc_4/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_4/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/4-a61.o[0] 4-a61.o
 * sha256: b2924cda843edb597709665da21c05cd9f5774dd07acb96e939b1fd6df281472
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: putchar
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: putchar.c */
#include "library/psx_bios_tailjump.h"

void putchar(char arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3d);
}

#endif
