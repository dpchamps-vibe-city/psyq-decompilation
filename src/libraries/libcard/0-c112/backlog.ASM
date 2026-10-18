.include "build/libraries/nonmatchings/libcard_0/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_0/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/0-c112.o[0] 0-c112.o
 * sha256: aeb6087f93a93ca4d91f6cf11a53cf2fe0099b698bfd756fb322e732f332c6f9
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _bu_init
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _bu_init.c */
#include "library/psx_bios_tailjump.h"

void _bu_init(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x70);
}

#endif
