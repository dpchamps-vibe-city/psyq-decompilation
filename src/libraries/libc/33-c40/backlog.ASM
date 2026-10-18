.include "build/libraries/nonmatchings/libc_33/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_33/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/33-c40.o[0] 33-c40.o
 * sha256: 39efd532ea67e3b640a880c32508c2e7ac13e2ec0466be5bfb4dda0762bc3200
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: bzero
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: bzero.c */
#include "library/psx_bios_tailjump.h"

void *bzero(unsigned char *arg0, int arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x28);
}

#endif
