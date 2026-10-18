.include "build/libraries/nonmatchings/libapi_14/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_14/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/14-c160.o[0] 14-c160.o
 * sha256: 18bd79addb5d2e81c7b0c791df905eff71cea965fcb6c9e5b3c54212d2bd2b46
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _boot
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _boot.c */
#include "library/psx_bios_tailjump.h"

void _boot(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0xa0);
}

#endif
