.include "build/libraries/nonmatchings/libapi_30/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_30/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/30-a16.o[0] 30-a16.o
 * sha256: 51b65b5667aeb9b45da220794bea3f787f204471f0fe16b94af572a8679e8544
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: ChangeTh
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: ChangeTh.c */
#include "library/psx_bios_tailjump.h"

int ChangeTh(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x10);
}

#endif
