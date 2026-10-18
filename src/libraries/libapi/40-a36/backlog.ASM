.include "build/libraries/nonmatchings/libapi_40/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_40/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/40-a36.o[0] 40-a36.o
 * sha256: 0020590822f236acf4f56943077b6d0241be61a1014b7756e09c562decd649a3
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: EnterCriticalSection
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: EnterCriticalSection.c */
#include "library/psx_bios.h"

int EnterCriticalSection(void) {
    return PSX_BIOS_SYSCALL(1);
}

#endif
