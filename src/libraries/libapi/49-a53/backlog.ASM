.include "build/libraries/nonmatchings/libapi_49/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_49/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/49-a53.o[0] 49-a53.o
 * sha256: 183010c9e020a2afb5aa9eb4f66235d18695311e12dad0f40d3610c724500c52
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: write
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: write.c */
#include "library/psx_bios_tailjump.h"

long write(long arg0, void *arg1, long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0x35);
}

#endif
