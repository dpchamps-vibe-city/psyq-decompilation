.include "build/libraries/nonmatchings/libc_21/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_21/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/21-c27.o[0] 21-c27.o
 * sha256: 83f8ba4ae7aeb2815ce297d32a42bb177350ce7f91054ca2b078373092d0b7bd
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strlen
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strlen.c */
#include "library/psx_bios_tailjump.h"

unsigned int strlen() {
    PSX_BIOS_TAILJUMP(0xa0, 0x1b);
}

#endif
