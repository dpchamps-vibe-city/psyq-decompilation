.include "build/libraries/nonmatchings/libapi_51/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_51/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/51-a55.o[0] 51-a55.o
 * sha256: ae078b4ebf17cac546214205a4830d1baf80ce9ed027db58b4cc3c8d3160a36e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: ioctl
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: ioctl.c */
#include "library/psx_bios_tailjump.h"

long ioctl(long arg0, long arg1, long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0x37);
}

#endif
