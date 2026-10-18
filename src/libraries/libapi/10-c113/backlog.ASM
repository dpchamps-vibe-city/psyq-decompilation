.include "build/libraries/nonmatchings/libapi_10/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_10/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/10-c113.o[0] 10-c113.o
 * sha256: b2e6343bffeec5c251089eb8107d774200aaddccfadfc6d52e3a9d7c2a67a1a9
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _96_init
 */
#include "common.h"
#include "include_asm.h"
#include "library/psx_bios_tailjump.h"


/* Preserved pre-switch part: _96_init.c */
void _96_init(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x71);
}

#endif
