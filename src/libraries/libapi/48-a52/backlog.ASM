.include "build/libraries/nonmatchings/libapi_48/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_48/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/48-a52.o[0] 48-a52.o
 * sha256: 9ecb47f0e76f08d18423af0773c54b6da03824783b97c52f9d2d6027ef8ee910
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: read
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: read.c */
#include "library/psx_bios_tailjump.h"

long read(long arg0, void *arg1, long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0x34);
}

#endif
