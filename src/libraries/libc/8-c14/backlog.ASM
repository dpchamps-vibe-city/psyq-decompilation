.include "build/libraries/nonmatchings/libc_8/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_8/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/8-c14.o[0] 8-c14.o
 * sha256: b8e00f39bb3c17a940a0fb611878482633ad68e4d48909e9a1cdb862996a273f
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: abs
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: abs.c */
#include "library/psx_bios_tailjump.h"

int abs(int arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0xe);
}

#endif
