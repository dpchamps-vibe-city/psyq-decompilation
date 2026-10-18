.include "build/libraries/nonmatchings/libc_40/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_40/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/40-c52.o[0] 40-c52.o
 * sha256: 82174e8629a4b0752b6ee88606cafc847c95133d92e7e98d825caeeca749ed92
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: free
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: free.c */
#include "library/psx_bios_tailjump.h"

void free(void *arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x34);
}

#endif
