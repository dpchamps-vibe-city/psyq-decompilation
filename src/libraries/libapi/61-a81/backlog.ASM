.include "build/libraries/nonmatchings/libapi_61/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_61/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/61-a81.o[0] 61-a81.o
 * sha256: 7241deedbe598cc64b4de6ca1b459d1ebf89fdee36063300d754ce63c5f349f4
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: Krom2RawAdd
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: Krom2RawAdd.c */
#include "library/psx_bios_tailjump.h"

long Krom2RawAdd(unsigned long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x51);
}

#endif
