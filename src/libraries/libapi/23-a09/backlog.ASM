.include "build/libraries/nonmatchings/libapi_23/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_23/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/23-a09.o[0] 23-a09.o
 * sha256: 19ac7a64aa7ab2891d096c3fb771079c6f3f8d9630f5831088057ae7cebae61c
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: CloseEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: CloseEvent.c */
#include "library/psx_bios_tailjump.h"

long CloseEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x9);
}

#endif
