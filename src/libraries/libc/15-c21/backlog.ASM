.include "build/libraries/nonmatchings/libc_15/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_15/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/15-c21.o[0] 15-c21.o
 * sha256: 875341b408c61215c2f77f7ef2f09071612e38ab893f13f179bf0c8e0e7bae1d
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strcat
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strcat.c */
#include "library/psx_bios_tailjump.h"

char *strcat(char *arg0, const char *arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x15);
}

#endif
