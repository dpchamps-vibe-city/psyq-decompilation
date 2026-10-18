.include "build/libraries/nonmatchings/libc_17/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_17/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/17-c23.o[0] 17-c23.o
 * sha256: 6d3bf900e4def3db5504ea1430ff1c27ea7e5dfcc01ec0a05e24470c1b5a739d
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strcmp
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strcmp.c */
#include "library/psx_bios_tailjump.h"

int strcmp() {
    PSX_BIOS_TAILJUMP(0xa0, 0x17);
}

#endif
