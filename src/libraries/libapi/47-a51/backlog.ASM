.include "build/libraries/nonmatchings/libapi_47/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_47/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/47-a51.o[0] 47-a51.o
 * sha256: 4b9b65d1f2fb1bd96561351e490109d67b1490debb038cb7050d08dbdfb57b7e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: lseek
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: lseek.c */
#include "library/psx_bios_tailjump.h"

long lseek(long arg0, long arg1, long arg2) {
    PSX_BIOS_TAILJUMP(0xb0, 0x33);
}

#endif
