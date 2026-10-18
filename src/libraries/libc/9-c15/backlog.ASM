.include "build/libraries/nonmatchings/libc_9/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_9/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/9-c15.o[0] 9-c15.o
 * sha256: ea2ba46fdcf5934abe62e0d29e16db4bd4a0aa54d1cbca473be0d353eea718cb
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: labs
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: labs.c */
#include "library/psx_bios_tailjump.h"

long labs(long arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0xf);
}

#endif
