.include "build/libraries/nonmatchings/libc_39/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_39/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/39-c51.o[0] 39-c51.o
 * sha256: e497abe80fa0066895c7b3c94939474328da44614ce2bee7f416d48a81b7bc50
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: malloc
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: malloc.c */
#include <malloc.h>
#include "library/psx_bios_tailjump.h"

void *malloc(u32 arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x33);
}

#endif
