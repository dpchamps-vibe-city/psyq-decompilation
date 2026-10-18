.include "build/libraries/nonmatchings/libapi_22/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_22/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/22-a08.o[0] 22-a08.o
 * sha256: b4431af2e813ffa300ad92f528eef1e959f37191a2b20f210868d50c05044dc0
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: OpenEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: OpenEvent.c */
#include "library/psx_bios_tailjump.h"

long OpenEvent(unsigned long arg0, long arg1, long arg2, long (*func)()) {
    PSX_BIOS_TAILJUMP(0xb0, 0x8);
}

#endif
