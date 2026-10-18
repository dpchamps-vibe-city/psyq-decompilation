.include "build/libraries/nonmatchings/libc_30/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_30/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/30-c37.o[0] 30-c37.o
 * sha256: 307675260ba23a72e19587158d7aa13ee1505864b7f2c5fd959f17b6d7fd1965
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: toupper
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: toupper.c */
#include "library/psx_bios_tailjump.h"

char toupper(char arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x25);
}

#endif
