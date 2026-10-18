.include "build/libraries/nonmatchings/libc_25/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_25/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/25-c31.o[0] 25-c31.o
 * sha256: 5ebe57a2ee46863b81bd786d675407100ff82f54295ca3c9695f10a5f7535b65
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strrchr
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strrchr.c */
#include "library/psx_bios_tailjump.h"

char *strrchr(const char *arg0, char arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1f);
}

#endif
