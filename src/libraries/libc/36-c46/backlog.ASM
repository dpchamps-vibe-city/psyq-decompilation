.include "build/libraries/nonmatchings/libc_36/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_36/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/36-c46.o[0] 36-c46.o
 * sha256: 9f77d9282541d307882da257308a9fb48934c5eff8d328abd338a1bc8294f139
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: memchr
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: memchr.c */
#include "library/psx_bios_tailjump.h"

void *memchr(const unsigned char *arg0, unsigned char arg1, int arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x2e);
}

#endif
