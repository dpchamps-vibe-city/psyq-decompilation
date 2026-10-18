.include "build/libraries/nonmatchings/libapi_15/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_15/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/15-c161.o[0] 15-c161.o
 * sha256: 6a3faab6e59e717cc25781625ce72b465c0dbe76f8d9dd733cacc236ed65bc03
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: SystemError
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: SystemError.c */
#include "library/psx_bios_tailjump.h"

void SystemError(char arg0, long arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0xa1);
}

#endif
