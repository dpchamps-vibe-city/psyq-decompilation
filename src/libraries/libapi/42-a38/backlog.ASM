.include "build/libraries/nonmatchings/libapi_42/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_42/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/42-a38.o[0] 42-a38.o
 * sha256: 14964d66e4df5430a5a7bd91c9302f971bc6bf06dbdd242d7291996a053be192
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: Exception
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: Exception.c */
#include "library/psx_bios.h"

void Exception(void) {
    (void)PSX_BIOS_SYSCALL(0);
}

#endif
