.include "build/libraries/nonmatchings/libcard_11/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_11/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/11-a92.o[0] 11-a92.o
 * sha256: a5e9173f8095cf64ed45b6d628b36cb2221c2fbe03fe7ba6dde00b84806643be
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_status
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_status.c */
#include "library/psx_bios_tailjump.h"

long _card_status(long drv) {
    PSX_BIOS_TAILJUMP(0xb0, 0x5c);
}

#endif
