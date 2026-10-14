#include "library/psx_bios_tailjump.h"

void srand(unsigned int arg0) {
    PSX_BIOS_TAILJUMP(0xa0, 0x30);
}
