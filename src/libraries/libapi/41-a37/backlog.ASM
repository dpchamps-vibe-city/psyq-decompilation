.include "build/libraries/nonmatchings/libapi_41/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_41/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/41-a37.o[0] 41-a37.o
 * sha256: 558c8bb0bc1fdadd6816d8bba340dde562b49bc8c6c55bd43676aa115a1c9c41
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: ExitCriticalSection
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: ExitCriticalSection.c */
#include "library/psx_bios.h"

void ExitCriticalSection(void) {
    (void)PSX_BIOS_SYSCALL(2);
}

#endif
