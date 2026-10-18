.include "build/libraries/nonmatchings/libapi_21/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_21/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/21-a07.o[0] 21-a07.o
 * sha256: 5d6fdc4748450524ec4f23ba81cba1bcf6292e1122ee7c7a80a542585fb3ba93
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: DeliverEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: DeliverEvent.c */
#include "library/psx_bios_tailjump.h"

void DeliverEvent(unsigned long arg0, unsigned long arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x7);
}

#endif
