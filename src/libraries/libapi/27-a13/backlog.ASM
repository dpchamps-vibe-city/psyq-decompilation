.include "build/libraries/nonmatchings/libapi_27/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_27/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/27-a13.o[0] 27-a13.o
 * sha256: 1841e9892a1a4445391c884d77da03289f2f1bd8b17970e30492a700e086521f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: DisableEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: DisableEvent.c */
#include "library/psx_bios_tailjump.h"

long DisableEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xd);
}

#endif
