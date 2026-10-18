.include "build/libraries/nonmatchings/libapi_13/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_13/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/13-c159.o[0] 13-c159.o
 * sha256: db9bb65658d06ba564339bb62ff96c0f303b73b7540762b63c610db5b0e7677e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: SetMem
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: SetMem.c */
#include "library/psx_bios_tailjump.h"

void SetMem(long arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x9f);
}

#endif
