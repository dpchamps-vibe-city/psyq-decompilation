.include "build/libraries/nonmatchings/libapi_7/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_7/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/7-c81.o[0] 7-c81.o
 * sha256: fa39b77bb57a62ad5b5fe36e41e6a557723e24b5d0dea347e20ea63e0ea5d858
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: LoadExec
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: LoadExec.c */
#include "library/psx_bios_tailjump.h"

long LoadExec(char *arg0, unsigned long arg1, unsigned long arg2) {
    PSX_BIOS_TAILJUMP(0xa0, 0x51);
}

#endif
