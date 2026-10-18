.include "build/libraries/nonmatchings/libapi_28/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_28/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/28-a14.o[0] 28-a14.o
 * sha256: c51c081d4499869f0761455608a5454b28c289d3bbb2d7d355e7e0fdb9724c5c
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: OpenTh
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: OpenTh.c */
#include "library/psx_bios_tailjump.h"

long OpenTh(long (*func)(), unsigned long arg1, unsigned long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0xe);
}

#endif
