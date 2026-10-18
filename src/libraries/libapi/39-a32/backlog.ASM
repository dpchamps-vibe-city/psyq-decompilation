.include "build/libraries/nonmatchings/libapi_39/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_39/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/39-a32.o[0] 39-a32.o
 * sha256: 505e449615d77378696efe9851a9d0e7856ea8eae5baf8f3778f6de3717fa126
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: UnDeliverEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: UnDeliverEvent.c */
#include "library/psx_bios_tailjump.h"

void UnDeliverEvent(unsigned long arg0, unsigned long arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x20);
}

#endif
