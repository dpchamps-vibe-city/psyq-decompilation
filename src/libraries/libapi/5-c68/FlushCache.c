#include "library/psx_bios_tailjump.h"

void FlushCache(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x44);
}
