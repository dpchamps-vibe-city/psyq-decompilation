.include "build/libraries/nonmatchings/libapi_53/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_53/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/53-a65.o[0] 53-a65.o
 * sha256: 9b5e83d26a64e5e3bb66f7bf9d6bf472d140b6b79e0ae8e2800631e9e678337c
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: format
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: format.c */
#include "library/psx_bios_tailjump.h"

long format(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x41);
}

#endif
