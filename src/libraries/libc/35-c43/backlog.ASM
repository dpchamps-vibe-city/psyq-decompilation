.include "build/libraries/nonmatchings/libc_35/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_35/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/35-c43.o[0] 35-c43.o
 * sha256: b3ce84d9a75b05e2b133f1d5b9c2d950fdd6b6b24b7dc93dd62153f8de6ee989
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: memset
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: memset.c */
#include "library/psx_bios_tailjump.h"

void *memset() {
    PSX_BIOS_TAILJUMP(0xa0, 0x2b);
}

#endif
