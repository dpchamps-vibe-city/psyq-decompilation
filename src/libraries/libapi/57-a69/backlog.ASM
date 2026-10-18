.include "build/libraries/nonmatchings/libapi_57/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_57/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/57-a69.o[0] 57-a69.o
 * sha256: bfaff8406531f14563ee5df2557849dab9b6e6dcbd2703db784a794b5aa74ecb
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: erase
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: erase.c */
#include "library/psx_bios_tailjump.h"

long erase(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x45);
}

#endif
