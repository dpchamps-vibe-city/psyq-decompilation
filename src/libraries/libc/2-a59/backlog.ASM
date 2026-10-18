.include "build/libraries/nonmatchings/libc_2/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_2/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/2-a59.o[0] 2-a59.o
 * sha256: 9f7e7db06387ba84d4d5fe9a66226749e5c2cf60a94fafd029c1b0845ff30661
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: putc
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: putc.c */
#include "library/psx_bios_tailjump.h"

void putc(char arg0, int arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3b);
}

#endif
