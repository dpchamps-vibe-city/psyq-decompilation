.include "build/libraries/nonmatchings/libc_43/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_43/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/43-c56.o[0] 43-c56.o
 * sha256: 82482b3435b86cfbe6b0ded09c5365794af494935a11fc2896c847111a951021
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: realloc
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: realloc.c */
#include <malloc.h>
#include "library/psx_bios_tailjump.h"

void *realloc(void *arg0, u32 arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x38);
}

#endif
