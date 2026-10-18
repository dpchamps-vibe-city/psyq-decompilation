.include "build/libraries/nonmatchings/libc_27/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_27/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/27-c33.o[0] 27-c33.o
 * sha256: 393861ddebe0a0d8af0db1017d9e90c2991d39f2857f3f0a2e3016d0ccec88eb
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strspn
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strspn.c */
#include "library/psx_bios_tailjump.h"

int strspn(const char *arg0, const char *arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x21);
}

#endif
