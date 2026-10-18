.include "build/libraries/nonmatchings/libapi_36/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_36/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/36-a23.o[0] 36-a23.o
 * sha256: 3ab45fb99097c89da9c40f137fba6b13a26336c6a4cd2e7e556e5871855d4937
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: ReturnFromException
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: ReturnFromException.c */
#include "library/psx_bios_tailjump.h"

void ReturnFromException(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x17);
}

#endif
