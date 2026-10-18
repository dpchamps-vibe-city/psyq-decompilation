.include "build/libraries/nonmatchings/libapi_46/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_46/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/46-a50.o[0] 46-a50.o
 * sha256: a523713824712e8aaaff91d1b79e5261ad0cf475e924177a68656b22066b3605
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: open
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: open.c */
#include "library/psx_bios_tailjump.h"

long open(char *arg0, unsigned long arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x32);
}

#endif
