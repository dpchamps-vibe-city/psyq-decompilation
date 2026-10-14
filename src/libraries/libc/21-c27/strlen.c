#include "library/psx_bios_tailjump.h"

unsigned int strlen() {
    PSX_BIOS_TAILJUMP(0xa0, 0x1b);
}
