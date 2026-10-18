.include "build/libraries/nonmatchings/libapi_29/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_29/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/29-a15.o[0] 29-a15.o
 * sha256: e6e3f64fa1ebb3bbeb18dfae63d3edb89d8b4f3fd548352180b26b1d3dc5edab
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: CloseTh
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: CloseTh.c */
#include "library/psx_bios_tailjump.h"

int CloseTh(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0xf);
}

#endif
