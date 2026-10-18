.include "build/libraries/nonmatchings/libc_31/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_31/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/31-c38.o[0] 31-c38.o
 * sha256: 5b2879705a9442a1053a4e8f0fd7d26b8c707fdd2db4d980f22f4a4749138ef3
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: tolower
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: tolower.c */
#include "library/psx_bios_tailjump.h"

char tolower(char arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x26);
}

#endif
