.include "build/libraries/nonmatchings/libapi_8/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_8/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/8-c82.o[0] 8-c82.o
 * sha256: ca2bc90fa6bcc883d32404163a393bf39404d6b9565bc5c7620ceafec5c8aaac
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: GetSysSp
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: GetSysSp.c */
#include "library/psx_bios_tailjump.h"

unsigned long GetSysSp(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x52);
}

#endif
