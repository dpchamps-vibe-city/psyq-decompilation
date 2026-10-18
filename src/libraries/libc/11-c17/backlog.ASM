.include "build/libraries/nonmatchings/libc_11/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_11/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/11-c17.o[0] 11-c17.o
 * sha256: 743b467f09216fe18ed810350946544b5f637bf985762961bc06aaa3d22fb089
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: atol
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: atol.c */
#include "library/psx_bios_tailjump.h"

long atol(const char *arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x11);
}

#endif
