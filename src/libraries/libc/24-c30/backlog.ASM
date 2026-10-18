.include "build/libraries/nonmatchings/libc_24/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_24/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/24-c30.o[0] 24-c30.o
 * sha256: f8c84248ef43aa08e5282b4958ae002c00d6048ddd05e1cc8c1c273318c10f63
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strchr
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strchr.c */
#include "library/psx_bios_tailjump.h"

char *strchr(const char *arg0, char arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1e);
}

#endif
