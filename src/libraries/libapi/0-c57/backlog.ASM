.include "build/libraries/nonmatchings/libapi_0/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_0/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/0-c57.o[0] 0-c57.o
 * sha256: 75de3c620e849a420e64f9a62a0806f94bfb7d6956753d8bb430ee526406949a
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: InitHeap
 */
#include "library/psx_bios_tailjump.h"


/* Preserved pre-switch part: InitHeap.c */
void InitHeap(unsigned long *arg0, unsigned long arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x39);
}

#endif
