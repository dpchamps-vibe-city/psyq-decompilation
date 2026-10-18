.include "build/libraries/nonmatchings/libapi_25/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_25/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/25-a11.o[0] 25-a11.o
 * sha256: 50af6e28a11dc310eee505ee8b32c3f0e73c3188c702cd1d35705673049b8697
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: TestEvent
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: TestEvent.c */
#include "library/psx_bios_tailjump.h"

long TestEvent(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xb);
}

#endif
