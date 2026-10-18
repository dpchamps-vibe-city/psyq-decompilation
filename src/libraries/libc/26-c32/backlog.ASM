.include "build/libraries/nonmatchings/libc_26/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_26/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/26-c32.o[0] 26-c32.o
 * sha256: e52190a4885db6f424d650c034cf7954d6b99a1a01d068d016b1020b1203ebe9
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strpbrk
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strpbrk.c */
#include "library/psx_bios_tailjump.h"

char *strpbrk(const char *arg0, const char *arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x20);
}

#endif
