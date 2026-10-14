#include "library/psx_bios_tailjump.h"

void *memcpy() {
    PSX_BIOS_TAILJUMP(0xa0, 0x2a);
}
