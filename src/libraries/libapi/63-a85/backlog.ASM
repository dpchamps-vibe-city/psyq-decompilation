.include "build/libraries/nonmatchings/libapi_63/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_63/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/63-a85.o[0] 63-a85.o
 * sha256: 0d857df1d6b57e40dedf01b28f287d599056bf18d5d775a52c4c2e4fd59cc232
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _get_error
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _get_error.c */
#include "library/psx_bios_tailjump.h"

long _get_error(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x55);
}

#endif
