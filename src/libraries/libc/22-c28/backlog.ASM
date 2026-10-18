.include "build/libraries/nonmatchings/libc_22/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_22/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/22-c28.o[0] 22-c28.o
 * sha256: d561de3cc8986eb36672066643c46ed23ee237398ed605aacab2fa5e5edeba1e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: index
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: index.c */
#include "library/psx_bios_tailjump.h"

char *index(const char *arg0, char arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x1c);
}

#endif
