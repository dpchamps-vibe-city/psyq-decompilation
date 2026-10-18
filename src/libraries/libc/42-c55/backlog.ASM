.include "build/libraries/nonmatchings/libc_42/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_42/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/42-c55.o[0] 42-c55.o
 * sha256: 674cb0450e873152398201fd85a3bba2dfbe7bba312fc374e0ae11a7e4e2d17b
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: calloc
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: calloc.c */
#include <malloc.h>
#include "library/psx_bios_tailjump.h"

void *calloc(u32 arg0, u32 arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x37);
}

#endif
