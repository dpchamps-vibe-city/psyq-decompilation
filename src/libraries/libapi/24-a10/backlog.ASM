.include "build/libraries/nonmatchings/libapi_24/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_24/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/24-a10.o[0] 24-a10.o
 * sha256: acc7c13d48502d0163ac9263b6fbfbf3bb46c510e7b76103e982421457f313cc
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: WaitEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: WaitEvent.c */
#include "library/psx_bios_tailjump.h"

long WaitEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xa);
}

#endif
