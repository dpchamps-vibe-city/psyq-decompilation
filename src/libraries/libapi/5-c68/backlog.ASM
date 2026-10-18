.include "build/libraries/nonmatchings/libapi_5/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_5/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/5-c68.o[0] 5-c68.o
 * sha256: 2609f58601e899bb507c3b5f08d018b555f749f86d4dbd641a00ed41939d794c
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: FlushCache
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: FlushCache.c */
#include "library/psx_bios_tailjump.h"

void FlushCache(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x44);
}

#endif
