#include "library/psx_bios_tailjump.h"

extern void *B_0000011C;

void DisablePAD(void) {
    PSX_BIOS_TAILJUMP_LOAD(B_0000011C);
}
