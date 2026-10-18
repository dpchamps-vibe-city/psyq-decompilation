.include "build/libraries/nonmatchings/libapi_26/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_26/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/26-a12.o[0] 26-a12.o
 * sha256: b0a38c7c8ffbd24c4ce3e2483c7eef977d12e2250176c836c64239bb162f4e61
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: EnableEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: EnableEvent.c */
#include "library/psx_bios_tailjump.h"

long EnableEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xc);
}

#endif
