.include "build/libraries/nonmatchings/libcard_1/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_1/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/1-c171.o[0] 1-c171.o
 * sha256: b2555eb1d64bc848ccc76e1dfd0fdb021e12b6cf24c4432ec66c3538f992ca1f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_info
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_info.c */
#include "library/psx_bios_tailjump.h"

long _card_info(long chan) {
    PSX_BIOS_TAILJUMP(0xa0, 0xab);
}

#endif
