.include "build/libraries/nonmatchings/libapi_52/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_52/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/52-a64.o[0] 52-a64.o
 * sha256: 3a4ad3e9172e6b66cdf8b1e3f485aee0a1ac7ddf3328423588538092e95b4a8a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: cd
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: cd.c */
#include "library/psx_bios_tailjump.h"

long cd(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x40);
}

#endif
