.include "build/libraries/nonmatchings/libapi_12/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_12/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/12-c157.o[0] 12-c157.o
 * sha256: 950cf001c5a9ac1cfce789515bbfb9ab3aafc39d93b48a5c59aee95154f68315
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: GetConf
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: GetConf.c */
#include "library/psx_bios_tailjump.h"

void GetConf(unsigned long *arg0, unsigned long *arg1, unsigned long *arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x9d);
}

#endif
