.include "build/libraries/nonmatchings/libapi_64/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_64/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/64-a91.o[0] 64-a91.o
 * sha256: a1780d3736fc9d84f2d6fb41d3e7b2ab8b3cfb1288e8e4bc5acd9fc78f7cfdff
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: ChangeClearPAD
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: ChangeClearPAD.c */
#include "library/psx_bios_tailjump.h"

void ChangeClearPAD(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x5b);
}

#endif
