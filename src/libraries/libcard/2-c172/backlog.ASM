.include "build/libraries/nonmatchings/libcard_2/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_2/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/2-c172.o[0] 2-c172.o
 * sha256: b997b260772cc26d2ddb3d938994aa2f4c5f08a0955e994cb7afe8b000e8a36a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_load
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_load.c */
#include "library/psx_bios_tailjump.h"

long _card_load(long chan) {
    PSX_BIOS_TAILJUMP(0xa0, 0xac);
}

#endif
