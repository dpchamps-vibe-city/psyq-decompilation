.include "build/libraries/nonmatchings/libapi_50/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_50/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/50-a54.o[0] 50-a54.o
 * sha256: 7c3c9eddfd1ef7d23cfe2abcaa3109612948e9e81209912a255583e97595b467
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: close
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: close.c */
#include "library/psx_bios_tailjump.h"

long close(long arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x36);
}

#endif
